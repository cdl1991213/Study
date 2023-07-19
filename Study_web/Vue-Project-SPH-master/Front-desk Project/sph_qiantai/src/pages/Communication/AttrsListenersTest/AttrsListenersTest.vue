<template>
  <div>
     <h1>Element插件:提供的全局组件</h1>
     <el-button type="primary" icon="el-icon-plus" size="mini" @click="handler">主要按钮</el-button>
     <el-button type="info" icon="el-icon-goods" size="mini">信息按钮</el-button>
     <el-button type="success" icon="el-icon-delete" size="mini">成功按钮</el-button>
     <el-button type="danger" icon="el-icon-remove" size="mini">危险按钮</el-button>
     <el-button type="warning" icon="el-icon-phone" size="mini">警告按钮</el-button>
     <h1>对于el-button进行二次封装</h1>
     <hintButton type="warning" icon="el-icon-s-help" size="mini" tip="豪哥提示信息" @click="handler"></hintButton>
  </div>
</template>

<script type="text/ecmascript-6">
  export default {
    name: 'AttrsListenersTest',

    methods: {
      handler(){
        alert(123);
      }
    },
  }
</script>
