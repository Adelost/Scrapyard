var fs = require("fs");
var path = require('path')

// Path to WebStorm project (".idea" folder)
var PROJECT_PATH = "D:/_Windows/Desktop/AberrantTemp";

// Files to be excluded form the project
var TARGETS = {
    ".cdt": true,
    "target": true
};

var folders = findFoldersToExclude(PROJECT_PATH);
// var content = readFile("/home/eeiijlr/Source/Java/BSS/com.ericsson.bss.rmca/ui/.idea/ui.iml");
console.log(folders);

function findFoldersToExclude(path) {
    var foldersPaths = findPathsToExclude(path);
    var folders = foldersPaths.map(function (path) {
        return path.replace(PROJECT_PATH, "");
    });
    return folders;
}

function findPathsToExclude(path) {
    var files = readFiles(path);
    var folders = filterFolders(files);
    var cmakeFiles = filterCmakeFiles(files);

    var topFolders = findFolders(path);
    var found = topFolders.reduce(function (total, topFolder) {
        if (topFolder in TARGETS) {
            return total.concat(path + "/" + topFolder);
        }
        var foundChildren = findPathsToExclude(path + "/" + topFolder);
        return total.concat(foundChildren);
    }, []);
    return found;
}

function readFiles(path) {
    return fs.readdirSync(path);
}

function filterFolders(files) {
    return files.filter(function (file) {
        return fs.lstatSync(file).isDirectory();
    });
}

function filterCmakeFiles(files) {
    return files.filter(function (file) {
        var ext = path.extname(file)
        return ext === ".h" || ".cpp" //;
    });
}

function getExcluded(content) {
    var matches = content.match(new RegExp(EXCLUDED_START + '.*' + EXCLUDED_END, "g"));
    var excluded = matches.map(function (match) {
        return match.match(new RegExp(EXCLUDED_START + "(.*)" + EXCLUDED_END))[1];
    });
    return excluded;
}

function readFile(path) {
    return fs.readFileSync(path, {encoding: 'utf8'});
}