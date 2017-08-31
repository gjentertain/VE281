const sort = require('./build/Release/sort');
const async = require('neo-async');
const pify = require('pify');

const arr = sort.generate("test", 1000000);
const buf = Buffer.from(arr.buffer);

setTimeout(async () => {
    const newBuf = Buffer.from(buf);

    console.log(newBuf.readInt32LE(0));
    console.log(buf.readInt32LE(0));

    sort.sort(newBuf);

    //console.log(arr[0]);
    console.log(newBuf.readInt32LE(0));
    console.log(buf.readInt32LE(0));
}, 0);


