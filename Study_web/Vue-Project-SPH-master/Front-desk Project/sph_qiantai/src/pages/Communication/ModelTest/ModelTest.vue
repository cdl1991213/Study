<template>
  <div>
    <h2>深入v-model</h2>
    <input type="text" v-model="msg" />
    <span>{{ msg }}</span>
    <h2>v-model底层实现原理</h2>
    <input type="text" placeholder="与v-model功能一样" :value="msg1" @input="handler"/>
    <span>{{ msg1 }}</span>
    <hr />
    <h2>父组件{{msg2}}</h2>
    <!-- <CustomInput :value="msg2" @input="inputHandler"></CustomInput> -->
    <!-- 底下的代码与顶上的代码原理一样的 -->
    <CustomInput v-model="msg2"></CustomInput>

    <!-- 底下是element-UI提供组件 -->
    <h3>{{msg3}}</h3>
    <el-input size="mini" v-model="msg3"></el-input>
  </div>
</template>

<script type="text/ecmascript-6">
import CustomInput from './CustomInput.vue'
export default {
  name: 'ModelTest',
  components: {
    CustomInput
  },
  data() {
    return {
      msg:"我是豪哥",
      msg1:'我是豪哥',
      msg2:"我爱豪哥",
      msg3:'我是element里面组件'
    }
  },
  methods: {
     handler(e){
       this.msg1 = e.target.value;
     },
     //自定义事件input回调
     inputHandler(params){
        this.msg2  = params;
     }
  },
}
</script>
