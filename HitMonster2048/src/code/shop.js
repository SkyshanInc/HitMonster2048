var Shop = {

	//打折
	//saleOption:[GOLD,GEM,PVE,ITEM,GENERAL,SODIER,SLOT,POWERUP],
	saleOption:null,
	init:function(){
		//初始化打折信息
		this.saleOption = [];
		for(var k in SALE_TYPE){
			this.saleOption[SALE_TYPE[k]-1] = 1;
		}
	},
	
	setSaleOption:function(saleList) {
		if(!this.saleOption) this.init();
		var discounts = saleList.discounts;//[{"type":8,"discount":0.6}]
		for(var i=0;i<discounts.length;i++){
			var saleInfo = discounts[i];
			this.saleOption[saleInfo.type-1] = saleInfo.discount;
		}
	},
	
	getSale:function(saleType) {
		if(!this.saleOption) return null;
		
		var saleInfo = {"result":{"type":saleType,"discount":this.saleOption[saleType-1]}}
		return saleInfo;
	},
	
	isSale:function(saleType){
		return this.getSale(saleType) != 1;
	}
}