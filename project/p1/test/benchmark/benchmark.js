const sort = require('./build/Release/sort');
const async = require('neo-async');
const pify = require('pify');

const SIZE = 10000;
// const arr = sort.generate("test", SIZE);
// const buf = Buffer.from(arr.buffer);

const buf = sort.generate("test", SIZE);
const clocks_per_sec = sort.getClocksPerSec();

console.log(clocks_per_sec);

setTimeout(async () => {

    for (let i = 0; i < 7; i++) {

        const wrapped = async.timeout(async (args, callback) => {
            const func = async () => {
                return new Promise((resolve, reject) => {
                    setTimeout(() => reject(0), 1);
                    const newBuf = Buffer.from(buf);
                    const time = sort.sort(newBuf, args[0]);
                    resolve(time);
                });
            };
            const time = await func();
            callback(null, time);
        }, 100);

        wrapped([i], function (err, data) {
            if (err) console.log(err);
            else console.log(data);
        });


        /*const wrapped = async.timeout(async (args, callback) => {
            const newBuf = Buffer.from(buf);
            const func = async () => {
                return new Promise((resolve, reject) => {
                    const time = sort.sort(newBuf, args[0]);
                    resolve(time);
                    setTimeout(() => reject(0), 1);
                });
            };
            const time = await func();
            callback(null, time);
        }, 100);

        wrapped([i], function (err, data) {
            if (err) console.log('>1s');
            else console.log(`${data / clocks_per_sec}s`);
        });*/


        // for (let j = 0; j < SIZE; j++) {
        //     console.log(newBuf.readInt32LE(j * 4));
        // }

    }

}, 0);


