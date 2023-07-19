<template>
  <div id="app" name="all">
    <Header></Header>
    <router-view></router-view>
    <Footer v-show="$route.meta.showFooter"></Footer>
  </div>
</template>

<script>
import Header from './components/Header'
import Footer from './components/Footer'

export default{
  name:'App',
  components:{
    Header,
    Footer
  },
  mounted(){
    // 请求 三级联动 接口数据
    this.$store.dispatch("categoryList_actions");
  }
}
</script>

<style>

</style>
