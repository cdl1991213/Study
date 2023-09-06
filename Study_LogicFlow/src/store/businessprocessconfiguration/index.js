import {reqBusinessProcessTemplate1, reqBusinessProcessTemplate2} from '@/api';
// 存储数据
const state = {
    businessProcessTemplateData:[],
}
// 响应组件动作
const actions = {
    async businessProcessTemplate1_actions({commit}){
        let response = await reqBusinessProcessTemplate1();
        if(response.code == 200){
            commit("businessProcessTemplate_mutations", response.data)
        }
    },
    async businessProcessTemplate2_actions({commit}){
        let response = await reqBusinessProcessTemplate2();
        if(response.code == 200){
            commit("businessProcessTemplate_mutations", response.data)
        }
    },


}
// 操作数据(state)
const mutations = {
    businessProcessTemplate_mutations(state, businessProcessTemplateData){
        state.businessProcessTemplateData = businessProcessTemplateData
    },

}
// 计算属性
const getters = {}

export default {
    state,
    actions,
    mutations,
    getters
}