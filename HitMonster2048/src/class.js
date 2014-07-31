
var Class = {
    extend: function (subClass, superClass) {
        function F() { };
        F.prototype = superClass.prototype;//原型继承
        subClass.prototype = new F();
        subClass.prototype.constructor = subClass;
        subClass._super = superClass.prototype;
        if (superClass.prototype.constructor == Object.prototype.constructor) {
            superClass.prototype.constructor = superClass;
        }
    },

    clone: function (target) {
        function F() { };
        F.prototype = target.prototype;//原型继承
        return new F();
    }
};