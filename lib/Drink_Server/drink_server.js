const express = require("express");
const {Client} = require("pg");
const bodyparser = require("body-parser");
const net = require('net');
const client = new Client({
    user: 'BarBot',
    host: '127.0.0.1',
    database: 'BarBot',
    password: 'w1X8jH@^8j$G',
    port: 5432,
});
client.connect();


// Service Code
async function get_fluids() {
    try {
        let {rows} = await client.query("SELECT * FROM fluid;");
        return rows;
    } catch (e) {
        return e;
    }
}

async function get_drinks() {
    try {
        let {rows} = await client.query("SELECT *, drink.id as drinkid FROM drink LEFT JOIN drink_name ON id = drink_id LEFT JOIN fluid ON drink.fluid = fluid.id;");
        let drinks = {};
        for (let row of rows) {
            if (!drinks.hasOwnProperty(row['drinkid'])) {
                drinks[row['drinkid']] = {name: row['drink_name'], fluids: []};
            }

            drinks[row['drinkid']]['fluids'].push({id: row['fluid'], amount: row['amount'], name: row['name']})
        }
        return drinks;
    } catch (e) {
        console.log(e);
        return e;
    }
}

async function pour(id) {
    try {
        let {rows} = await client.query("SELECT fluid, amount FROM drink WHERE id = $1", [id]);
        for (let ingredient of rows) {
            if (connected_fluids.indexOf(ingredient['fluid']) === -1) {
                return {error: "Not all ingredients available"}
            }
        }

        await client.query("INSERT INTO poured_drink (drink) VALUES ($1)", [id]);
        return {}
    } catch (e) {
        return e;
    }
}

// HTTP Code

    let app = express();

    let connected_fluids = [0, 1, 2, 3];


    app.use(express.static("public/"));
    app.use(bodyparser.json());


    /**
     * Route to retrieve all known fluids
     */
    app.get("/fluids", async (req, res) => {
        res.end(JSON.stringify(await get_fluids()));
    });

    app.post("/drinks/save", async (req, res) => {
        try {
            let drink = req.body;
            let {rows} = await client.query("INSERT INTO drink_name (drink_name) VALUES ($1) RETURNING drink_id", [drink.name])
            let id = rows[0]['drink_id'];

            let i = 1;
            let paramString = drink['ingredients'].map(ingredient => {
                let str = "($" + i + ",$" + (i + 1) + ",$" + (i + 2) + ")";
                i += 3;
                return str;
            });

            let paremeters = drink['ingredients'].map(ingredient => {
                return [id, ingredient.id, ingredient.amount];
            }).flat();

            await client.query("INSERT INTO drink (id, fluid, amount) VALUES " + paramString, paremeters);
            res.end("{}")
        } catch (e) {
            console.log(e);
            res.end(JSON.stringify(e))
        }
    });

    app.get("/pump_fluids", async (req, res) => {
            res.end(JSON.stringify(connected_fluids));
        }
    );

    app.post("/fluids/save", async (req, res) => {
        try {
            let drink = req.body;
            await client.query("INSERT INTO fluid (name) VALUES ($1)", [drink.name]);
            res.end("{}")
        } catch (e) {
            console.log(e);
            res.end(JSON.stringify(e))
        }
    });

    app.get("/fluids/remove/:id", async (req, res) => {
        try {
            await client.query("DELETE FROM fluid WHERE id = $1", [req.params.id]);
            res.end("{}");
        } catch (e) {
            console.log(e);
            res.end(JSON.stringify(e))
        }
    });

    app.get("/drinks/remove/:id", async (req, res) => {
        try {
            await client.query("DELETE FROM drink WHERE id = $1", [req.params.id]);
            await client.query("DELETE FROM drink_name WHERE drink_id = $1", [req.params.id]);
            res.end("{}");
        } catch (e) {
            console.log(e);
            res.end(JSON.stringify(e))
        }
    })

    app.get("/drinks", async (req, res) => {
        res.end(JSON.stringify(await get_drinks()));
    });

    /**
     * Route to switch the bottle connected to a pump
     */
    app.get("/connect_pump/:pump/:fluid", (req, res) => {
        connected_fluids[parseInt(req.params.pump)] = parseInt(req.params.fluid);
        console.log(connected_fluids);
        res.end();
    });

    /**
     * Route to pour a drink:
     * Retrieves all ingredients from the database, checks if they are connected to a pump
     * If so, pushes a poured_drink to the database
     */
    app.get("/pour/:id", async (req, res) => {
        res.end(JSON.stringify( await pour(req.params.id)));
    });

    /**
     * Retrieves the required pump times for the first poured_drink that has poured=false
     * Sets poured to true on this record after
     */
    app.get("/pumps", async (req, res) => {
        let amounts = Array(connected_fluids.length).fill("0");
        try {

            let {rows: poured_drinks} = await client.query("SELECT * FROM poured_drink WHERE poured = false ORDER BY moment ASC LIMIT 1;");
            if (poured_drinks.length === 0) {
                return res.end(amounts.join(" "))
            }

            let {rows: fluids} = await client.query("SELECT * FROM drink WHERE id = $1;", [poured_drinks[0]['drink']]);

            for (let fluid of fluids) {
                amounts[connected_fluids.indexOf(fluid['fluid'])] = fluid['amount'] + "";
            }

            await client.query("UPDATE poured_drink SET poured=true WHERE id = $1", [poured_drinks[0]['id']])
            return res.end(amounts.join(" "));
        } catch (e) {
            console.log(e);
            res.end(amounts.join(" "));
        }
    });


    app.listen(8443);

// Socket Code
{
    let DELIMITER = ":-:";
    let server = net.createServer(function (socket) {
        socket.on('data', async (data) => {
            let response = await handle_command(data.toString().split(DELIMITER));
            console.log(response);
            if(response.length >0)
                send_response(socket, response);
        });
        socket.on('error', (err) => {
        })
    });

    server.listen(8444, '192.168.1.5');

    function send_response(socket, response) {
        socket.write(response.join(DELIMITER))
    }

    function fluid_map(amount = false) {
        return (fluid) => {
            return amount ? [fluid.id, fluid.name, fluid.amount] : [fluid.id, fluid.name];
        }

    }

    function drink_flatten(drinks) {
        let newDrinks = [];
        for (let d in drinks) {
            if(!drinks.hasOwnProperty(d))
                continue;
            newDrinks.push(d);
            newDrinks.push(drinks[d].name);
            for (let f of drinks[d].fluids) {
                newDrinks.push(...fluid_map(true)(f));
            }
            newDrinks.push("::end::");
        }
        return newDrinks;
    }

    async function handle_command(command) {
        if(command[0] === "get_fluids"){
            let fluids = await get_fluids();
            return fluids.map(fluid_map(false)).flat();
        } else if (command[0] === "get_drinks") {
            let drinks = await get_drinks();
            return drink_flatten(drinks);
        } else if(command[0] === "get_connected_fluids") {
            let fluids = await get_fluids();
            return fluids.filter(x => connected_fluids.indexOf(x.id) > -1).map(fluid_map(false)).flat();
        } else if(command[0] === "pour") {
            let result = await pour(command[1]);
            if(result.error)
                return ["error"];
            else
                return ["success"];

        }
            return ['JALf'];
    }
}