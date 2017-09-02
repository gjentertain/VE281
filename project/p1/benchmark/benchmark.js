const sort = require('./build/Release/sort');
const gauge = require('gauge');
const bar = new gauge(process.stderr, {
    updateInterval: 1,
    cleanupOnExit: true
});
bar.show();

const SIZE = 1e8;
const EXP_MAX = 7;
const buf = sort.generate("test", SIZE);
const CLOCKS_PER_SEC = sort.getClocksPerSec();
const MAX_TIME = 1 * CLOCKS_PER_SEC;

const ALGORITHM_MAX = 7;
const ALGORITHM_NAME = [
    "bubble",
    "insertion",
    "selection",
    "merge",
    "quick_extra",
    "quick_in_place",
    "cpp_standard",
];
const ALGORITHM_ACTIVE = [];
for (let i = 0; i < ALGORITHM_MAX; i++) {
    ALGORITHM_ACTIVE.push(true);
}

const REPEAT_TIMES = [100, 10, 5, 2, 2, 2, 1];
const WEIGHT_ARR = [1, 2, 5, 5, 5, 2, 1];


let tasks = [];
let base = 1;
let weight_all = 0;
for (let exp = 0; exp < EXP_MAX; exp++) {
    base *= 10;
    let size = 0;
    for (let mul = 1; mul <= 9; mul++) {
        size += base;
        for (let i = 0; i < ALGORITHM_MAX; i++) {
            let weight = WEIGHT_ARR[exp];
            weight_all += weight;
            tasks.push({
                size: size,
                order: i,
                times: REPEAT_TIMES[exp],
                weight: weight
            });
        }
    }
}

let queue = [];
let progress = 0;

tasks.forEach((value) => {
    queue.push(() => {
        progress += 1 / weight_all * value.weight;

        if (!ALGORITHM_ACTIVE[value.order]) {
            return [value, -1];
        }

        const newBuf = Buffer.from(buf.slice(0, value.size * value.times * 4));
        const averageTime = sort.sort(newBuf, value.order, value.size, value.times) / value.times;

        if (averageTime > MAX_TIME) {
            ALGORITHM_ACTIVE[value.order] = false;
            //console.log(value.order);
        }

        return [value, averageTime];
    });
});

const func = () => {

    const [data, averageTime] = (queue.shift())();

    if (averageTime > 0) {
        const time = Math.round(averageTime) / CLOCKS_PER_SEC;
        const blanks = "                    ";
        console.log(`size: ${data.size}, algorithm: ${ALGORITHM_NAME[data.order]}, time: ${time}s ${blanks}`);
    }

    if (tasks.length) {
        const task = tasks.shift();
        bar.show(`${Math.round(progress * 100)}%`, progress);
        bar.pulse(`size: ${task.size}, algorithm: ${ALGORITHM_NAME[task.order]}`);
    }

    if (queue.length) {
        setTimeout(func, 0);
    }
};

tasks.shift();
func();


