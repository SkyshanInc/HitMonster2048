var SimpleGesturesRight = 0;
var SimpleGesturesLeft = 1;
var SimpleGesturesUp = 2;//
var SimpleGesturesDown = 3;//
var SimpleGesturesError = 4;//
var SimpleGesturesNotSupport = 5;




// class define
function SimpleRecognizer()
{
	this.result = SimpleGesturesError;
	this.x = 0;
	this.y = 0;
	this.points = [];
}

// be called in onTouchBegan
SimpleRecognizer.prototype.beginPoint = function(point)
{
	this.result = SimpleGesturesError;
    this.points = [];
	this.points.push(point);
}

SimpleRecognizer.prototype.movePoint = function(point)
{
	this.points.push(point);
}

SimpleRecognizer.prototype.endPoint = function(point)
{
    this.points.push(point);

	if (this.points.length < 3) {
		return SimpleGesturesError;
	}
    
	var newRtn = SimpleGesturesError;
	var len = this.points.length;
	//每当触点移动时,在当前触点和之前触点之间计算不同的x坐标和y坐标
	var dx = this.points[len - 1].x - this.points[0].x;
	var dy = this.points[len - 1].y - this.points[0].y;
    
    cc.log("dx:"+dx+",dy:"+dy);
    
	if (Math.abs(dx) > Math.abs(dy)) {
		//在这种情况下,运动趋势的触点在x轴方向
		if (dx > 0) {
			newRtn = SimpleGesturesRight;
		} else {
			newRtn = SimpleGesturesLeft;
		}
	} else {
		//在这种情况下,运动趋势的触点在y轴方向
		if (dy > 0) {
			newRtn = SimpleGesturesUp;
		} else {
			newRtn = SimpleGesturesDown;
		}
	}
    cc.log("result:"+this.result+",newRtn:"+newRtn);
	// first set result
	if (this.result == SimpleGesturesError || this.result == SimpleGesturesNotSupport) {
		this.result = newRtn;
	}
    
	// if diretcory change, not support Recongnizer
	if (this.result != newRtn) {
		this.result = SimpleGesturesNotSupport;
	}
    
//    if (newRtn != SimpleGesturesNotSupport && newRtn != SimpleGesturesError) {
//		this.result = newRtn;
//	}else{
//        this.result = SimpleGesturesNotSupport;
//    }
	return this.result;
}

SimpleRecognizer.prototype.getPoints = function()
{
	return this.points;
}