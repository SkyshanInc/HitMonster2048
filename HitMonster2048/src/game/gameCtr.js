var MAP_WIDTH = 16;
var MAP_HEIGHT = 9;

var GameManager = {
	enemyVector:[],
	bulletVector: [],
	towerVector: [],
	groupVector: [],
	blood: 0.0,
	money: 0,
	groupNum: 0,
	curMapName: '',
	currLevelFile: "",
	nextLevelFile: "",
	isFinishedAddGroup: false,
	curBgName: '',
	_curMapId: 0,



	setBlood: function(blood) {
		this.blood = blood;
	},
	getBlood: function() {
		return this.blood
	},
	setMoney: function(money) {
		this.money = money;

	},
	getMoney: function() {
		return this.money;

	},
	setGroupNum: function(groupNum) {
		this.groupNum = groupNum;

	},
	getGroupNum: function(groupNum) {
		return this.groupNum;

	},
	setCurMapName: function(curMapName) {
		this.curMapName = curMapName;
	},

	getCurMapName: function() {
		return this.curMapName ;
	},
	setCurrLevelFile: function(currLevelFile) {
		this.currLevelFile = currLevelFile;

	},
	getCurrLevelFile: function() {
		return this.currLevelFile ;

	},

	setNextLevelFile: function(nextLevelFile) {
		this.nextLevelFile = nextLevelFile;

	},
	getNextLevelFile: function() {
		return this.nextLevelFile ;

	},
	// IsFinishedAddGroup:function(isFinishedAddGroup){
	// 	this.isFinishedAddGroup = isFinishedAddGroup

	// };
	setCurBgName: function(curBgName) {
		this.curBgName = curBgName;
	},
	getCurBgName: function() {
		return this.curBgName ;
	},

	setCurMapID: function(curID) {
		this._curMapId = curID;
	},
	getCurMapID: function() {
		return this._curMapId;
	},

	clear: function() {
		this.enemyVector.clear();
		this.bulletVector.clear();
		//towerVector.clear();
		this.groupVector.clear();
	},
	getInstance:function(){
		return this;
	}
    
}