var NetWorkData = {}
/*
*  Login
*/
NetWorkData.login = function(device_hash){
    return {
        method:"login",
        params:{
            "device_hash":device_hash
        }
    }
}
/*
*  Init
*/
NetWorkData.init = function(device_hash){
    return {
        method:"init",
        params:{
            "device_hash":device_hash
        }
    }
}