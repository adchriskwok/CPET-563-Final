function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "ads1015_Test"};
	this.sidHashMap["ads1015_Test"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Display"] = {sid: "ads1015_Test:10"};
	this.sidHashMap["ads1015_Test:10"] = {rtwname: "<Root>/Display"};
	this.rtwnameHashMap["<Root>/adc"] = {sid: "ads1015_Test:6"};
	this.sidHashMap["ads1015_Test:6"] = {rtwname: "<Root>/adc"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
