//引入相应的路由组件
import home from '@/pages/home';
import Search from '@/pages/search';
import Login from '@/pages/login';
import Register from '@/pages/register';
import Detail from '@/pages/detail';
import AddCartSuccess from '@/pages/addCartSuccess'
import ShopCart from '@/pages/shopCart'
import Trade from '@/pages/trade';
import Pay from '@/pages/pay'
import PaySuccess from '@/pages/paySuccess';
import Center from '@/pages/center'



//个人中心的二级路由组件
import MyOrder from '@/pages/center/myOrder';
import TeamOrder from '@/pages/center/teamOrder'
export default [
    {
        path: '/home',
        name: 'erha',
        component: home,
        //路由元信息,新学习的一个配置项!!!!给当前路由添加一些额外数据
        //它的右侧是一个对象[可以有多个键值对]
        //路由配置项：书写的时候不要胡写、乱写、瞎写【在VC组件身上获取不到,没有任何意义】
        meta: { show: true },
    }
    ,
    {
        //命名路由,给路由起一个名字
        name: 'search',
        //在注册路由的时候,如果这里占位，切记务必要传递params
        path: '/search/:keyword?',
        component: Search,
        meta: { show: true },
        //新增配置项:props,给路由组件传递props参数
        //第一种布尔模式,相当于把params参数，作为props属性值传递给这个路由组件
        // props:true,

        //第二种:对象形式
        // props:{a:1,b:'我爱你'}

        //第三种写法:函数写法.一般是把query参数与params参数当中props传递给路由组件!!!
        //route就是当前路由
        // props:(route)=>{
        //      //是将当前箭头函数返回结果，作为props传递给search路由组件!!!
        //      return {a:route.params.keyword,b:'可以传递参数'};
        // }
    }
    ,
    {
        path: '/login',
        component: Login,
        meta: { show: false },
    }
    ,
    {
        path: '/register',
        component: Register,
        meta: { show: false },
    }
    ,
    //重定向到首页
    {
        path: '/',
        redirect: '/home'
    }
    ,
    {
        path: '/detail/:skuId?',
        component: Detail,
        //路由元信息,控制当前路由是否需要Footer组件
        meta: { show: true },
    },
    {
        path: '/addcartsuccess',
        component: AddCartSuccess,
        //路由元信息,控制当前路由是否需要Footer组件
        meta: { show: true },
    }
    ,
    {
        path: '/shopcart',
        component: ShopCart,
        meta: { show: true }
    },
    {
        path: '/trade',
        component: Trade,
        meta: { show: true }
    },
    {
        path: '/pay',
        component: Pay,
        meta: { show: true }
    },
    {
        path: '/paysuccess',
        component: PaySuccess,
        meta: { show: true }
    }
    ,
    {
        path: '/center',
        component: Center,
        meta: { show: true },
        //二级路由配置的地方
        children:[
             //我的订单
             {
                  path:'myorder',
                  component:MyOrder
             }
             ,
             {
                 path:'teamorder',
                 component:TeamOrder
             }
             ,
             {
                 path:'/center',
                 redirect:'/center/myorder'
             }
        ]
    },
    {
        path: '/communication',
        component: () => import('@/pages/Communication/Communication'),
        children: [
          {
            path: 'event',
            component: () => import('@/pages/Communication/EventTest/EventTest'),
            meta: {
             show: false
            },
          },
          {
            path: 'model',
            component: () => import('@/pages/Communication/ModelTest/ModelTest'),
            meta: {
                show: false
            },
          },
          {
            path: 'sync',
            component: () => import('@/pages/Communication/SyncTest/SyncTest'),
            meta: {
                show: false
            },
          },
          {
            path: 'attrs-listeners',
            component: () => import('@/pages/Communication/AttrsListenersTest/AttrsListenersTest'),
            meta: {
                show: false
            },
          },
          {
            path: 'children-parent',
            component: () => import('@/pages/Communication/ChildrenParentTest/ChildrenParentTest'),
            meta: {
                show: false
            },
          },
          {
            path: 'scope-slot',
            component: () => import('@/pages/Communication/ScopeSlotTest/ScopeSlotTest'),
            meta: {
                show: false
            },
          }
        ],
      },
]