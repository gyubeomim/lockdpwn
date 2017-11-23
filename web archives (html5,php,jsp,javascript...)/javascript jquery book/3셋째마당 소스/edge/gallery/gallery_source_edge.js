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
                rect: ['0', '0','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c1_btn.png",'0px','0px']
            },
            {
                id: 'c2_btn',
                type: 'image',
                rect: ['0', '0','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c2_btn.png",'0px','0px']
            },
            {
                id: 'c3_btn',
                type: 'image',
                rect: ['0', '0','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c3_btn.png",'0px','0px']
            },
            {
                id: 'c4_btn',
                type: 'image',
                rect: ['0', '0','50px','50px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"c4_btn.png",'0px','0px']
            }],
            symbolInstances: [

            ]
        },
    states: {
        "Base State": {
            "${_Stage}": [
                ["color", "background-color", 'rgba(255,255,255,1)'],
                ["style", "width", '550px'],
                ["style", "height", '400px'],
                ["style", "overflow", 'hidden']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 0,
            autoPlay: true,
            timeline: [
            ]
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
