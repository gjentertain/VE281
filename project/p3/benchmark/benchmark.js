const fs = require('fs');
const path = require('path');
const addon = require('./build/Release/queue');
const gauge = require('gauge');
const bar = new gauge(process.stderr, {
    updateInterval: 1,
    cleanupOnExit: true
});
bar.show();

const SIZE = 1e8;
const EXP_MAX = 4;
const buf = addon.generate("test", SIZE);
const CLOCKS_PER_SEC = addon.getClocksPerSec();
const MAX_TIME = 1 * CLOCKS_PER_SEC;

const ALGORITHM_MAX = 4;
const ALGORITHM_NAME = [
    "binary",
    "unsorted",
    "fibonacci",
    "cpp_standard"
];
const ALGORITHM_ACTIVE = [];
let result = [];
for (let i = 0; i < ALGORITHM_MAX; i++) {
    ALGORITHM_ACTIVE.push(true);
    result.push(null);
}


const REPEAT_TIMES = [100, 10, 2, 1, 1, 1, 1];
const PARTITION_ARR = [100, 100, 50, 50, 20, 20, 20];
const WEIGHT_ARR = require('./progress.json');
let total_time = [0, 0, 0, 0, 0, 0, 0];


let tasks = [];
let base = 1;
let weight_all = 0;


for (let exp = 0; exp < EXP_MAX; exp++) {
    let size = base;
    let partition = PARTITION_ARR[exp];
    base *= 10;
    for (let mul = 1; mul < partition - 1 && size < base; mul++) {
        //console.log(size, base, Math.ceil(base / partition ));
        for (let i = 0; i < ALGORITHM_MAX; i++) {
            let weight = WEIGHT_ARR[exp] || 1;
            weight_all += weight;
            tasks.push({
                size: size,
                order: i,
                times: REPEAT_TIMES[exp],
                weight: weight,
                exp: exp
            });
        }
        size += Math.ceil(base / partition);
    }
}


let queue = [];
let progress = 0;

tasks.forEach((value) => {
    queue.push(() => {
        progress += 1 / weight_all * value.weight;

        if (!ALGORITHM_ACTIVE[value.order]) {
            result[value.order] = null;
            return [value, -1];
        }

        const newBuf = Buffer.from(buf.slice(0, value.size * value.size * value.times * 4));
        const totalTime = addon.queue(newBuf, value.order, value.size, value.size, value.times);
        const averageTime = totalTime / value.times;
        total_time[value.exp] += totalTime;

        result[value.order] = newBuf;
        if (averageTime > MAX_TIME) {
            ALGORITHM_ACTIVE[value.order] = false;
            //console.log(value.order);
        }

        /*if (value.order === ALGORITHM_MAX - 1) {
            for (let i = 0; i < value.order; i++) {
                const temp = result[i];
                if (temp && Buffer.compare(temp, result[value.order]) !== 0) {
                    //console.error(value.size, ALGORITHM_NAME[i]);
                }
            }
        }*/

        return [value, averageTime];
    });
});

const file = fs.openSync(path.resolve(__dirname, 'result'), 'w');


const func = () => {

    const [data, averageTime] = (queue.shift())();

    if (averageTime > 0) {
        const time = Math.round(averageTime) / CLOCKS_PER_SEC;
        const blanks = "                    ";
        console.log(`size: ${data.size}, algorithm: ${ALGORITHM_NAME[data.order]}, time: ${time}s ${blanks}`);
        fs.writeSync(file, `${data.size} ${data.order} ${averageTime / CLOCKS_PER_SEC}\n`);
    }

    if (tasks.length) {
        const task = tasks.shift();
        bar.show(`${Math.round(progress * 100)}%`, progress);
        bar.pulse(`size: ${task.size}, algorithm: ${ALGORITHM_NAME[task.order]}`);
    }

    if (queue.length) {
        setTimeout(func, 0);
    } else {
        fs.closeSync(file);
        let data = [];
        total_time.forEach((value) => {
            const ratio = Math.round(value / total_time[0]);
            data.push(ratio);
            //console.log(ratio);
        });
        fs.writeFileSync(path.resolve(__dirname, 'progress.json'), JSON.stringify(data));
    }
};

tasks.shift();
func();


