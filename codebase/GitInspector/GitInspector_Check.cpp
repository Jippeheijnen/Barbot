

#include <fstream>
#include <iostream>

std::string PYTHON27_PATH = "C:\\Python27\\python.exe";

void gitinspector_validate();
void python27_validate();
void gitinspector_run();

int main() {
    std::cout << std::endl << std::endl;
    python27_validate();
    gitinspector_validate();
    gitinspector_run();

}
void gitinspector_run() {
    std::cout << "Alright! running Gitinspector, hold tight, this might take some time" << std::endl;
    std::string command = PYTHON27_PATH + " gitinspector/gitinspector.py --format=htmlembedded --timeline -w .. > ../codebase/GitInspector/Gitinspector_stats.html";
    system(command.c_str());
}

void gitinspector_validate() {
    std::cout << "Checking if gitinspector is already in the build folder" << std::endl;
    std::ifstream gitins("gitinspector/gitinspector.py");
    if(!gitins.good()) {
        std::cout << "* Gitinspector is not here :(" << std::endl;
        std::cout << "* Cloning the GitInspector repository, hold on" << std::endl;
        system("git clone https://github.com/ejwa/gitinspector");
    } else {
        std::cout << "* Gitinspector is already here, nice!" << std::endl;
    }
    std::cout << std::endl;
    gitins.close();
}

void python27_validate() {
    std::cout << "Validating if Python2.7 is installed in the default location" << std::endl;
    std::ifstream python27(PYTHON27_PATH);
    if(!python27.good()) {
        std::cout << "* Python 2.7 is not installed in default location :(" << std::endl;
        std::cout << "* Please install the given file:" << std::endl;
        std::ofstream psfile("download_python.ps1");
        std::string ps_script = "$down = New-Object System.Net.WebClient\r\n"
                                "$url  = 'https://www.python.org/ftp/python/2.7/python-2.7.amd64.msi';\r\n"
                                "$file = 'python.msi';\r\n"
                                "$down.DownloadFile($url,$file);\r\n";
        psfile.write(ps_script.c_str(), ps_script.size());
        psfile.close();
        std::cout << "* Downloading Python Installer" << std::endl;
        system("call powershell.exe -executionpolicy bypass -file download_python.ps1");
        std::cout << "* Running Python Installer" << std::endl;
        std::cout << "* Use the \"Install for all users\" option" << std::endl;
        system("python.msi");
    } else {
        std::cout << "* Python 2.7 is installed in default location, nice!" << std::endl;
    }
    std::cout << std::endl;
    python27.close();
}