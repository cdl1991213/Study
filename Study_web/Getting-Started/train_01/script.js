/*
参数：
    obj 要绑定事件的对象
    eventStr 事件的字符串（不含on）
    callback 回调函数
*/
function bind(obj, eventStr, callback){
    if(obj.addEventListener){
        //大部分浏览器兼容方式
        obj.addEventListener(eventStr, callback, false);
    }else{
        // IE8及以下
        obj.addEventListener("on"+eventStr, function(){
            callback.call(obj);
        });
    }
}
