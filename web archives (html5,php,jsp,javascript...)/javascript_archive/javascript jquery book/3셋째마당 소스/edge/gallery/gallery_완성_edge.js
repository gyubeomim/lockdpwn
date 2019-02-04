/**
 * Adobe Edge: symbol definitions
 */
(function($, Edge, compId){
//images folder
var im='images/';

var fonts = {};
var opts = {};
var resources = [
];
var symbols = {
"stage": {
    version: "3.0.0",
    minimumCompatibleVersion: "3.0.0",
    build: "3.0.0.322",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
            {
                id: 'bg',
                type: 'image',
                rect: ['0', '0','800px','480px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"bg.png",'0px','0px']
            },
            {
                id: 'c1_btn',
                type: 'image',
                rect: ['232px', '408px','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c1_btn.png",'0px','0px']
            },
            {
                id: 'c2_btn',
                type: 'image',
                rect: ['330px', '408px','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c2_btn.png",'0px','0px']
            },
            {
                id: 'c3_btn',
                type: 'image',
                rect: ['424px', '408px','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c3_btn.png",'0px','0px']
            },
            {
                id: 'c4_btn',
                type: 'image',
                rect: ['520px', '408px','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c4_btn.png",'0px','0px']
            },
            {
                id: 'car1',
                type: 'image',
                rect: ['-355px', '257px','325px','135px','auto', 'auto'],
                opacity: 1,
                fill: ["rgba(0,0,0,0)",im+"car1.png",'0px','0px']
            },
            {
                id: 'car2',
                type: 'image',
                rect: ['-355px', '257px','325px','135px','auto', 'auto'],
                opacity: 1,
                fill: ["rgba(0,0,0,0)",im+"car2.png",'0px','0px']
            },
            {
                id: 'car3',
                type: 'image',
                rect: ['-355px', '257px','325px','135px','auto', 'auto'],
                opacity: 1,
                fill: ["rgba(0,0,0,0)",im+"car3.png",'0px','0px']
            },
            {
                id: 'car4',
                type: 'image',
                rect: ['-355px', '257px','325px','135px','auto', 'auto'],
                opacity: 1,
                fill: ["rgba(0,0,0,0)",im+"car4.png",'0px','0px']
            }],
            symbolInstances: [

            ]
        },
    states: {
        "Base State": {
            "${_car4}": [
                ["style", "top", '257px'],
                ["style", "opacity", '0'],
                ["style", "left", '-355px']
            ],
            "${_car1}": [
                ["style", "top", '257px'],
                ["style", "opacity", '0'],
                ["style", "left", '-355px']
            ],
            "${_c3_btn}": [
                ["style", "top", '408px'],
                ["style", "left", '424px']
            ],
            "${_c4_btn}": [
                ["style", "top", '408px'],
                ["style", "left", '520px']
            ],
            "${_c2_btn}": [
                ["style", "top", '408px'],
                ["style", "left", '330px']
            ],
            "${_Stage}": [
                ["color", "background-color", 'rgba(255,255,255,1)'],
                ["style", "width", '800px'],
                ["style", "height", '480px'],
                ["style", "overflow", 'hidden']
            ],
            "${_car3}": [
                ["style", "top", '257px'],
                ["style", "opacity", '0'],
                ["style", "left", '-355px']
            ],
            "${_c1_btn}": [
                ["style", "top", '408px'],
                ["style", "left", '232px']
            ],
            "${_car2}": [
                ["style", "top", '257px'],
                ["style", "opacity", '0'],
                ["style", "left", '-355px']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 8000,
            autoPlay: true,
            timeline: [
                { id: "eid154", tween: [ "style", "${_car2}", "left", '255px', { fromValue: '-355px'}], position: 2000, duration: 1000 },
                { id: "eid161", tween: [ "style", "${_car2}", "left", '-355px', { fromValue: '255px'}], position: 4000, duration: 0 },
                { id: "eid150", tween: [ "style", "${_car2}", "opacity", '1', { fromValue: '0'}], position: 2000, duration: 1000 },
                { id: "eid157", tween: [ "style", "${_car2}", "opacity", '0', { fromValue: '1'}], position: 4000, duration: 0 },
                { id: "eid151", tween: [ "style", "${_car3}", "left", '255px', { fromValue: '-355px'}], position: 4000, duration: 1000 },
                { id: "eid160", tween: [ "style", "${_car3}", "left", '-355px', { fromValue: '255px'}], position: 6000, duration: 0 },
                { id: "eid153", tween: [ "style", "${_car4}", "left", '255px', { fromValue: '-355px'}], position: 6000, duration: 1000 },
                { id: "eid159", tween: [ "style", "${_car4}", "left", '-355px', { fromValue: '255px'}], position: 8000, duration: 0 },
                { id: "eid152", tween: [ "style", "${_car1}", "left", '255px', { fromValue: '-355px'}], position: 0, duration: 1000 },
                { id: "eid162", tween: [ "style", "${_car1}", "left", '-355px', { fromValue: '255px'}], position: 2000, duration: 0 },
                { id: "eid148", tween: [ "style", "${_car1}", "opacity", '1', { fromValue: '0'}], position: 0, duration: 1000 },
                { id: "eid158", tween: [ "style", "${_car1}", "opacity", '0', { fromValue: '1'}], position: 2000, duration: 0 },
                { id: "eid147", tween: [ "style", "${_car3}", "opacity", '1', { fromValue: '0'}], position: 4000, duration: 1000 },
                { id: "eid156", tween: [ "style", "${_car3}", "opacity", '0', { fromValue: '1'}], position: 6000, duration: 0 },
                { id: "eid149", tween: [ "style", "${_car4}", "opacity", '1', { fromValue: '0'}], position: 6000, duration: 1000 },
                { id: "eid155", tween: [ "style", "${_car4}", "opacity", '0', { fromValue: '1'}], position: 8000, duration: 0 }            ]
        }
    }
}
};


Edge.registerCompositionDefn(compId, symbols, fonts, resources, opts);

/**
 * Adobe Edge DOM Ready Event Handler
 */
$(window).ready(function() {
     Edge.launchComposition(compId);
});
})(jQuery, AdobeEdge, "EDGE-1287126");
