function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Blank Message */
	this.urlHashMap["ros_test:1"] = "ros_test.h:165";
	/* <Root>/Bus
Assignment */
	this.urlHashMap["ros_test:2"] = "ros_test.cpp:35";
	/* <Root>/Publish */
	this.urlHashMap["ros_test:4"] = "ros_test.cpp:42,48,105,117,124,133&ros_test.h:166";
	/* <Root>/Sine Wave */
	this.urlHashMap["ros_test:3"] = "ros_test.cpp:36&ros_test.h:56,59,62,65&ros_test_data.cpp:25,28,31,34";
	/* <S1>/Constant */
	this.urlHashMap["ros_test:1:33"] = "ros_test.h:68&ros_test_data.cpp:40";
	/* <S2>/SinkBlock */
	this.urlHashMap["ros_test:4:31"] = "ros_test.cpp:43,44,106,116,125,126,132&ros_test.h:49,50";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "ros_test"};
	this.sidHashMap["ros_test"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "ros_test:1"};
	this.sidHashMap["ros_test:1"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "ros_test:4"};
	this.sidHashMap["ros_test:4"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<Root>/Blank Message"] = {sid: "ros_test:1"};
	this.sidHashMap["ros_test:1"] = {rtwname: "<Root>/Blank Message"};
	this.rtwnameHashMap["<Root>/Bus Assignment"] = {sid: "ros_test:2"};
	this.sidHashMap["ros_test:2"] = {rtwname: "<Root>/Bus Assignment"};
	this.rtwnameHashMap["<Root>/Publish"] = {sid: "ros_test:4"};
	this.sidHashMap["ros_test:4"] = {rtwname: "<Root>/Publish"};
	this.rtwnameHashMap["<Root>/Sine Wave"] = {sid: "ros_test:3"};
	this.sidHashMap["ros_test:3"] = {rtwname: "<Root>/Sine Wave"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "ros_test:1:33"};
	this.sidHashMap["ros_test:1:33"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/Out"] = {sid: "ros_test:1:34"};
	this.sidHashMap["ros_test:1:34"] = {rtwname: "<S1>/Out"};
	this.rtwnameHashMap["<S2>/In1"] = {sid: "ros_test:4:29"};
	this.sidHashMap["ros_test:4:29"] = {rtwname: "<S2>/In1"};
	this.rtwnameHashMap["<S2>/SignalSpecification"] = {sid: "ros_test:4:30"};
	this.sidHashMap["ros_test:4:30"] = {rtwname: "<S2>/SignalSpecification"};
	this.rtwnameHashMap["<S2>/SinkBlock"] = {sid: "ros_test:4:31"};
	this.sidHashMap["ros_test:4:31"] = {rtwname: "<S2>/SinkBlock"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
