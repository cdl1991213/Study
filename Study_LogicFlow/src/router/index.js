/* 路由配置文件 */
import VueRouter from "vue-router"

// 引入路由组件
import Home from '@/pages/Home'
import BusinessProcessConfiguration from '@/pages/BusinessProcessConfiguration'

// 暴露router
export default new VueRouter({
    routes:[
        {   
            name:'Home',
            path:'/home',
            component:Home,
        },
        {   
            name:'BusinessProcessConfiguration',
            path:'/businessprocessconfiguration',
            component:BusinessProcessConfiguration,
        },
        // 项目重定向(重定向首页)
        {
            path:'/',
            redirect:'/home'
        },
    ]
})

// 重写VueRouter.prototype.push 方法
const routerPush = VueRouter.prototype.push;
VueRouter.prototype.push = function (location) {
    return routerPush.call(this, location).catch(err => {})
};
