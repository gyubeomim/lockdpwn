function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Blank Message */
	this.urlHashMap["ros_test2:1"] = "ros_test2.h:174";
	/* <Root>/Bus
Assignment */
	this.urlHashMap["ros_test2:2"] = "ros_test2.cpp:86";
	/* <Root>/Derivative */
	this.urlHashMap["ros_test2:6"] = "ros_test2.cpp:61,84,101,118,214&ros_test2.h:55,56,57,58";
	/* <Root>/Publish */
	this.urlHashMap["ros_test2:7"] = "ros_test2.cpp:89,95,200,212,242,251&ros_test2.h:175";
	/* <Root>/Subscribe */
	this.urlHashMap["ros_test2:3"] = "ros_test2.cpp:43,59,186,198,218,224,231,240&ros_test2.h:168,176";
	/* <S1>/Constant */
	this.urlHashMap["ros_test2:1:33"] = "ros_test2.h:74&ros_test2_data.cpp:39";
	/* <S2>/SinkBlock */
	this.urlHashMap["ros_test2:7:31"] = "ros_test2.cpp:90,91,201,211,243,244,250&ros_test2.h:60,61";
	/* <S3>/Constant */
	this.urlHashMap["ros_test2:3:51"] = "ros_test2.h:71&ros_test2_data.cpp:33";
	/* <S3>/Enabled
Subsystem */
	this.urlHashMap["ros_test2:3:52"] = "ros_test2.cpp:50,58,219,223&ros_test2.h:177";
	/* <S3>/SourceBlock */
	this.urlHashMap["ros_test2:3:58"] = "ros_test2.cpp:44,46,57,187,197,232,233,239&ros_test2.h:59,62";
	/* <S4>/In1 */
	this.urlHashMap["ros_test2:3:53"] = "ros_test2.cpp:45&ros_test2.h:50";
	/* <S4>/Enable */
	this.urlHashMap["ros_test2:3:54"] = "ros_test2.cpp:51";
	/* <S4>/Out1 */
	this.urlHashMap["ros_test2:3:55"] = "ros_test2.cpp:220&ros_test2.h:68&ros_test2_data.cpp:27";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "ros_test2"};
	this.sidHashMap["ros_test2"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "ros_test2:1"};
	this.sidHashMap["ros_test2:1"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "ros_test2:7"};
	this.sidHashMap["ros_test2:7"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "ros_test2:3"};
	this.sidHashMap["ros_test2:3"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "ros_test2:3:52"};
	this.sidHashMap["ros_test2:3:52"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<Root>/Blank Message"] = {sid: "ros_test2:1"};
	this.sidHashMap["ros_test2:1"] = {rtwname: "<Root>/Blank Message"};
	this.rtwnameHashMap["<Root>/Bus Assignment"] = {sid: "ros_test2:2"};
	this.sidHashMap["ros_test2:2"] = {rtwname: "<Root>/Bus Assignment"};
	this.rtwnameHashMap["<Root>/Bus Selector"] = {sid: "ros_test2:5"};
	this.sidHashMap["ros_test2:5"] = {rtwname: "<Root>/Bus Selector"};
	this.rtwnameHashMap["<Root>/Derivative"] = {sid: "ros_test2:6"};
	this.sidHashMap["ros_test2:6"] = {rtwname: "<Root>/Derivative"};
	this.rtwnameHashMap["<Root>/Publish"] = {sid: "ros_test2:7"};
	this.sidHashMap["ros_test2:7"] = {rtwname: "<Root>/Publish"};
	this.rtwnameHashMap["<Root>/Subscribe"] = {sid: "ros_test2:3"};
	this.sidHashMap["ros_test2:3"] = {rtwname: "<Root>/Subscribe"};
	this.rtwnameHashMap["<Root>/Terminator"] = {sid: "ros_test2:4"};
	this.sidHashMap["ros_test2:4"] = {rtwname: "<Root>/Terminator"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "ros_test2:1:33"};
	this.sidHashMap["ros_test2:1:33"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/Out"] = {sid: "ros_test2:1:34"};
	this.sidHashMap["ros_test2:1:34"] = {rtwname: "<S1>/Out"};
	this.rtwnameHashMap["<S2>/In1"] = {sid: "ros_test2:7:29"};
	this.sidHashMap["ros_test2:7:29"] = {rtwname: "<S2>/In1"};
	this.rtwnameHashMap["<S2>/SignalSpecification"] = {sid: "ros_test2:7:30"};
	this.sidHashMap["ros_test2:7:30"] = {rtwname: "<S2>/SignalSpecification"};
	this.rtwnameHashMap["<S2>/SinkBlock"] = {sid: "ros_test2:7:31"};
	this.sidHashMap["ros_test2:7:31"] = {rtwname: "<S2>/SinkBlock"};
	this.rtwnameHashMap["<S3>/Constant"] = {sid: "ros_test2:3:51"};
	this.sidHashMap["ros_test2:3:51"] = {rtwname: "<S3>/Constant"};
	this.rtwnameHashMap["<S3>/Enabled Subsystem"] = {sid: "ros_test2:3:52"};
	this.sidHashMap["ros_test2:3:52"] = {rtwname: "<S3>/Enabled Subsystem"};
	this.rtwnameHashMap["<S3>/SourceBlock"] = {sid: "ros_test2:3:58"};
	this.sidHashMap["ros_test2:3:58"] = {rtwname: "<S3>/SourceBlock"};
	this.rtwnameHashMap["<S3>/Out1"] = {sid: "ros_test2:3:59"};
	this.sidHashMap["ros_test2:3:59"] = {rtwname: "<S3>/Out1"};
	this.rtwnameHashMap["<S3>/Out2"] = {sid: "ros_test2:3:60"};
	this.sidHashMap["ros_test2:3:60"] = {rtwname: "<S3>/Out2"};
	this.rtwnameHashMap["<S4>/In1"] = {sid: "ros_test2:3:53"};
	this.sidHashMap["ros_test2:3:53"] = {rtwname: "<S4>/In1"};
	this.rtwnameHashMap["<S4>/Enable"] = {sid: "ros_test2:3:54"};
	this.sidHashMap["ros_test2:3:54"] = {rtwname: "<S4>/Enable"};
	this.rtwnameHashMap["<S4>/Out1"] = {sid: "ros_test2:3:55"};
	this.sidHashMap["ros_test2:3:55"] = {rtwname: "<S4>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
