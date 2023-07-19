import {reqSearchList} from '@/api';
// 存储数据
const state = {
    searchList:[],
    stateKeyword:''
}
// 响应组件动作
const actions = {
    // 获取 Search搜索 接口数据
    async searchList_actions({commit}, params={}){
        let response = await reqSearchList(params);
        if(response.code == 200){
            commit("searchList_mutations", response.data)
        }
    },

    // 修改keyword数据
    keyword_actions({commit}, newKeyword){
        commit("keyword_mutations", newKeyword)
    }
}
// 操作数据(state)
const mutations = {
    // 获取 Search搜索 接口数据
    searchList_mutations(state, searchList){
        state.searchList = searchList
    },

    // 修改keyword数据
    keyword_mutations(state, newKeyword){
        state.stateKeyword = newKeyword
    },
}
// 计算属性
const getters = {
    goodsList(state){
        // || [] 用于解决以下情况:
        // 网速较慢的情况下, 在state.searchList未获取到数据时, getters计算属性被调用
        return state.searchList.goodsList || []
    },
    trademarkList(state){
        return state.searchList.trademarkList || []
    },
    attrsList(state){
        return state.searchList.attrsList || []
    }
}

export default {
    state,
    actions,
    mutations,
    getters
}