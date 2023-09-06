// vuex状态管理器
import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex)

// 引入子仓库
import businessprocessconfiguration from './businessprocessconfiguration';

export default new Vuex.Store({
    modules:{
        businessprocessconfiguration
    }
})