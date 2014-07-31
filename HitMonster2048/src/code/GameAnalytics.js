var GameAnalytics = {
	setAccountInfo: function(userId, userName, level){
        GameAnalyticsMgr.getInstance().setAccountInfo(userId, userName, level);
    },
	levelUpgrade: function() {
    	GameAnalyticsMgr.getInstance().levelUpgrade(MainPlayer.get("level"));
	},
	onBeginMission: function(missionId) {
		GameAnalyticsMgr.getInstance().onBeginMission(missionId);
	},
	onCompleteMission: function(missionId) {
		GameAnalyticsMgr.getInstance().onCompleteMission(missionId);
	},
	onFailedMission: function(missionId) {
		GameAnalyticsMgr.getInstance().onFailedMission(missionId);
	},
	onPurchase: function(name, itemNumber, priceForOne) {
		GameAnalyticsMgr.getInstance().onPurchase(name, itemNumber, priceForOne);
	},
	onUse: function(name, number) {
		GameAnalyticsMgr.getInstance().onUse(name, number);
	},
	onReward: function(count, reason) {
		GameAnalyticsMgr.getInstance().onReward(count, reason);
	},
	onCustomEvent: function(name, params) {
        params["device_hash"] = MainPlayer.getName();
		GameAnalyticsMgr.getInstance().onCustomEvent(name, params);
	},
    
	onRecruitWithGem: function() {
    	GameAnalytics.onCustomEvent("RecruitWithGem", {});
	},
	onRecruitWithGold: function() {
		GameAnalytics.onCustomEvent("RecruitWithGold", {});
	},
	onFreeLottery: function() {
		GameAnalytics.onCustomEvent("FreeLottery", {});
	},
	onPaidLottery: function() {
		GameAnalytics.onCustomEvent("PaidLottery", {});
	},
    onRewardGold: function(amount, reason) {
        GameAnalytics.onCustomEvent("RewardGold", {amount: amount, reason: reason});
    },
    onGetAwards: function (awards, reason) {
        for (var i=0; i < awards.length; i++) {
            var typeID = awards[i].typeID;
            var amount = awards[i].amount;
            if (typeID === exports.configs.dimond_ID.value) {
                GameAnalytics.onReward(amount, reason);
            } else if (typeID === exports.configs.gold_ID.value) {
                GameAnalytics.onRewardGold(amount, reason);
            }
        }
    },
};





