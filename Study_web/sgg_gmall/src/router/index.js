/* 路由配置文件 */
import VueRouter from "vue-router"

// 引入路由组件
import Home from '@/pages/Home'
import Login from '@/pages/Login'
import Register from '@/pages/Register'
import Search from '@/pages/Search'

// 暴露router
export default new VueRouter({
    routes:[
        {   
            name:'Home',
            path:'/home',
            component:Home,
            meta:{
                showFooter:true
            }
        },
        {
            name:'Login',
            path:'/login',
            component:Login
        },
        {
            name:'Register',
            path:'/register',
            component:Register
        },
        {
            name:'Search',
            path:"/search/:keyword?",
            component:Search,
            meta:{
                showFooter:true
            }
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
