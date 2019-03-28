const express = require("express");
const {Client} = require("pg");
const client = new Client({
    user: 'BarBot',
    host: '127.0.0.1',
    database: 'BarBot',
    password: 'w1X8jH@^8j$G',
    port: 5432,
});
client.connect();

let app = express();

let connected_fluids = [0,1,2,3];


/**
 * Route to switch the bottle connected to a pump
 */
app.get("/connect_pump/:pump/:fluid", (req,res) => {
    connected_fluids[parseInt(req.params.pump)] = parseInt(req.params.fluid);
    res.end();
});

/**
 * Route to pour a drink:
 * Retrieves all ingredients from the database, checks if they are connected to a pump
 * If so, pushes a poured_drink to the database
 */
app.get("/pour/:id", async (req, res) => {
    try {
        let {rows} = await client.query("SELECT fluid, amount FROM drink WHERE drink_id = $1", [req.params.id]);
        for (let ingredient of rows) {
            if (connected_fluids.indexOf(ingredient['fluid']) === -1) {
                return res.end(JSON.stringify({error: "Not all ingredients available"}))
            }
        }

        await client.query("INSERT INTO poured_drink (drink) VALUES ($1)", [req.params.id]);
        res.end("{}")
    } catch(e) {
        res.end(JSON.stringify(e));
    }

});

/**
 * Retrieves the required pump times for the first poured_drink that has poured=false
 * Sets poured to true on this record after
 */
app.get("/pumps", async (req,res) => {
    let amounts = Array(connected_fluids.length).fill("0");
    try {

        let {rows: poured_drinks} = await client.query("SELECT * FROM poured_drink WHERE poured = false ORDER BY moment ASC LIMIT 1;");
        if (poured_drinks.length === 0) {
            console.log("No Drinks to Pour");
            return res.end(amounts.join(" "))
        }

        let {rows: fluids} = await client.query("SELECT * FROM drink WHERE drink_id = $1;", [poured_drinks[0]['drink']]);

        for (let fluid of fluids) {
            amounts[connected_fluids.indexOf(fluid['fluid'])] = fluid['amount'] + "";
        }

        await client.query("UPDATE poured_drink SET poured=true WHERE id = $1", [poured_drinks[0]['id']])
        return res.end(amounts.join(" "));
    } catch(e) {
        console.log(e);
        res.end(amounts.join(" "));
    }
});


app.listen(8443);