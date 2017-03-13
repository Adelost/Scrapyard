let fs = require("fs");
let path = require('path');

// Path to WebStorm project (".idea" folder)
const CMAKE_PATH = "/home/eeiijlr/Desktop/Sandbox/AberrantTemp";
const SOURCE_PATH = CMAKE_PATH + "/Source/Utils";
const IGNORED_FOLDERS = {
    "__old__": false
};
const HARD_CODED_FILES = ["Source/main.cpp"];

refreshCmake(SOURCE_PATH);

function refreshCmake(path) {
    let found = findCppFiles(path)
        .map(file => file.replace(CMAKE_PATH + "/", ""));
    let files = HARD_CODED_FILES.concat(found);
    setFilesInCmake(files);
    return files;
}

function setFilesInCmake(files) {
    const CMAKE_FILE = CMAKE_PATH + "/CMakeLists.txt";
    let lines = readFile(CMAKE_FILE)
        .split("\n");
    let newLines = [];
    let i = 0;
    // Start
    while (true) {
        let line = lines[i];
        i += 1;
        let setStart = "set(SOURCE_FILES";
        if (line.startsWith(setStart)) {
            newLines.push(setStart);
            break;
        }
        newLines.push(line);
    }
    // Set
    for (let file of files) {
        newLines.push("        " + file);
    }
    newLines.push("        )");
    while (true) {
        let line = lines[i];
        i += 1;
        if (line.endsWith(")")) {
            break;
        }
    }
    // End
    while (i < lines.length) {
        let line = lines[i];
        i += 1;
        newLines.push(line);
    }
    writeFile(CMAKE_FILE, newLines.join("\n"));
}

function findCppFiles(path) {
    let files = readFolder(path);
    let folders = filterFolders(files);
    let found = filterCppFiles(files);
    return folders.reduce((total, folder) => {
        let found = findCppFiles(folder)
        return total.concat(found);
    }, found);
}

function readFolder(parentPath) {
    return fs.readdirSync(parentPath)
        .map(path => parentPath + "/" + path);
}

function filterFolders(files) {
    return files.filter(file => {
        return fs.lstatSync(file).isDirectory()
            && !(path.basename(file) in IGNORED_FOLDERS);
    });
}

function filterCppFiles(files) {
    return files.filter(file => {
        let ext = path.extname(file);
        return ext === ".h" || ext == ".cpp";
    });
}

function readFile(path) {
    return fs.readFileSync(path, {encoding: 'utf8'});
}

function writeFile(path, content) {
    return fs.writeFileSync(path, content, {encoding: 'utf8'});
}
