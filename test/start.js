var path = require('path');
var dir = '../test/specs/';

[
    'dongdu'
].forEach((script) => {
    require(path.join(dir, script));
});