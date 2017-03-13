var fs = require("fs");

// Path to WebStorm project (".idea" folder)
var PROJECT_PATH = "/";

// Files to be excluded form the project
var TARGETS = {
    ".cdt": true,
    "target": true
};

var EXCLUDED_START = '<excludeFolder url="file://\\$MODULE_DIR\\$';
var EXCLUDED_END = '" />';


var folders = findFoldersToExclude(PROJECT_PATH);
var exclude
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

function findFolders(path) {
    var files = fs.readdirSync(path);
    var folders = files.filter(function (file) {
        return fs.lstatSync(path + "/" + file).isDirectory();
    });
    return folders;
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