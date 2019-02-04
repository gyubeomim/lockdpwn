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
                id: 'Ellipse',
                type: 'ellipse',
                rect: ['74px', '159px','80px','80px','auto', 'auto'],
                borderRadius: ["50%", "50%", "50%", "50%"],
                fill: ["rgba(192,192,192,1)",[50,50,false,'farthest-corner',[['rgba(0,0,253,1.00)',0],['rgba(0,1,15,1.00)',100]]]],
                stroke: [0,"rgba(0,0,0,1)","none"],
                boxShadow: ["", 3, 3, 3, 0, "rgba(0,0,0,0.65098)"]
            }],
            symbolInstances: [

            ]
        },
    states: {
        "Base State": {
            "${_Stage}": [
                ["color", "background-color", 'rgba(255,255,255,1)'],
                ["style", "overflow", 'hidden'],
                ["style", "height", '400px'],
                ["gradient", "background-image", [270,[['rgba(45,121,197,1.00)',0],['rgba(2,42,87,1.00)',100]]]],
                ["style", "width", '550px']
            ],
            "${_Ellipse}": [
                ["subproperty", "boxShadow.blur", '3px'],
                ["gradient", "background-image", [50,50,false,'farthest-corner',[['rgba(0,0,253,1.00)',0],['rgba(0,1,15,1.00)',100]]]],
                ["style", "left", '74px'],
                ["style", "width", '80px'],
                ["style", "top", '159px'],
                ["style", "height", '80px'],
                ["subproperty", "boxShadow.offsetV", '3px'],
                ["subproperty", "boxShadow.offsetH", '3px'],
                ["subproperty", "boxShadow.color", 'rgba(0,0,0,0.65098)']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 1000,
            autoPlay: true,
            timeline: [
                { id: "eid2", tween: [ "style", "${_Ellipse}", "left", '400px', { fromValue: '74px'}], position: 0, duration: 1000 }            ]
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
})(jQuery, AdobeEdge, "EDGE-27625140");
