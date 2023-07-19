import {reqBannerList, reqCategoryList, reqFloorList} from '@/api';
// 存储数据
const state = {
    categoryList:[],
    bannerList:[],
    floorList:[],
}
// 响应组件动作
const actions = {
    // 获取 typenav三级联动 接口数据
    async categoryList_actions({commit}){
        let response = await reqCategoryList();
        if(response.code == 200){
            commit("categoryList_mutations", response.data)
        }
    },

    // 获取 banner轮播图 接口数据
    async bannerList_actions({commit}){
        let response = await reqBannerList()
        if(response.code == 200){
            commit("bannerList_mutations", response.data)
        }
    },
    
    // 获取 floor列表 接口数据
    async floorList_actions({commit}){
        let response = await reqFloorList()
        if(response.code == 200){
            commit("floorList_mutations", response.data)
        }
    }
}
// 操作数据(state)
const mutations = {
    // 获取 typenav三级联动 接口数据
    categoryList_mutations(state, categoryList){
        state.categoryList = categoryList
    },

    // 获取 banner轮播图 接口数据
    bannerList_mutations(state, bannerList){
        state.bannerList = bannerList
    },

    // 获取 floor列表 接口数据
    floorList_mutations(state, floorList){
        state.floorList = floorList
    }
}
// 计算属性
const getters = {}

export default {
    state,
    actions,
    mutations,
    getters
}