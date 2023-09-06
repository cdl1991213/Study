import Vue from 'vue'
import VueRouter from "vue-router"
import App from './App.vue'
import router from '@/router';  // vue-router
import store from '@/store';  // vue-x
import '@/mock/mockServe' // mock

Vue.config.productionTip = false

Vue.use(VueRouter)

new Vue({
  render: h => h(App),
  router, // 注册路由vue-router
  store,  //注册仓库vuex
}).$mount('#app')
