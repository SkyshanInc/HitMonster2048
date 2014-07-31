
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask director the window size
        var size = cc.director.getWinSize();

        // add a "close" icon to exit the progress. it's an autorelease object
        var closeItem = cc.MenuItemImage.create(
            res.CloseNormal_png,
            res.CloseSelected_png,
            function () {
                cc.log("Menu is clicked!");
            }, this);
        closeItem.attr({
            x: size.width - 20,
            y: 20,
            anchorX: 0.5,
            anchorY: 0.5
        });

        var menu = cc.Menu.create(closeItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = 0;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = cc.Sprite.create(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2,
            scale: 0.5,
            rotation: 180
        });
        this.addChild(this.sprite, 0);

        var rotateToA = cc.RotateTo.create(2, 0);
        var scaleToA = cc.ScaleTo.create(2, 1, 1);

        this.sprite.runAction(cc.Sequence.create(rotateToA, scaleToA));
        helloLabel.runAction(cc.Spawn.create(cc.MoveBy.create(2.5, cc.p(0, size.height - 40)),cc.TintTo.create(2.5,255,125,0)));
                                      
                                      
           
        this.space = new cp.Space() ;

        this._debugNode = cc.PhysicsDebugNode.create( this.space );
        this._debugNode.visible = true ;
        this.addChild( this._debugNode );

        var space = this.space;
        var staticBody = space.staticBody;

        // Walls
        var winSize = size;
        var walls = [ new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),               // bottom
            new cp.SegmentShape( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),    // top
            new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),             // left
            new cp.SegmentShape( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)  // right
            ];
        for( var i=0; i < walls.length; i++ ) {
            var shape = walls[i];
            shape.setElasticity(1);
            shape.setFriction(1);
            space.addStaticShape( shape );
        }

    // Gravity
    space.gravity = cp.v(0, -100);



                                      
        cc.spriteFrameCache.addSpriteFrames(res.DemoLogin0_Plist);


        this.addChild(this.createPhysicsSprite(cc.p(size.width/2,size.height/2)));
                                        
        
        this.scheduleUpdate();
        return true;
    }
});

HelloWorldLayer.prototype.createPhysicsSprite = function( pos ) {
    var sprite = cc.PhysicsSprite.createWithSpriteFrameName("star2.png");

    var czWidth = sprite.getContentSize().width;
    var czHeight = sprite.getContentSize().height;
    var body = new cp.Body(1, cp.momentForBox(1, czWidth, czHeight+50) );
    body.setPos( pos );
    this.space.addBody( body );


    var shape = new cp.BoxShape( body, czWidth, czHeight);
    shape.setElasticity( 0.5 );
    shape.setFriction( 0.5 );
    this.space.addShape( shape );

    
    sprite.setBody( body );
    return sprite;
};
HelloWorldLayer.prototype.update = function( delta ) {
    this.space.step( delta );
};


