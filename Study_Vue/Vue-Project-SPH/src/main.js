import Vue from 'vue'
import VueRouter from "vue-router"
import App from './App.vue'
import router from '@/router';  // vue-router
import store from '@/store';  // vue-x

// 全局组件
import TypeNav from '@/components/TypeNav';
import Carousel from '@/components/Carousel';
import '@/mock/mockServe' // mock
import 'swiper/css/swiper.css'; // swiper

Vue.config.productionTip = false  // 关闭vue生产提示
Vue.use(VueRouter)

Vue.component(TypeNav.name, TypeNav) // 注册全局组件
Vue.component(Carousel.name, Carousel) // 注册全局组件

new Vue({
  render: h => h(App),
  router, // 注册路由vue-router
  store,  //注册仓库vuex
}).$mount('#app')
