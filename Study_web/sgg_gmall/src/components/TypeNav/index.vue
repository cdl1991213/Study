<template>
  <!-- 商品分类导航 -->
  <div class="type-nav">
    <div class="container">
      <div @mouseleave="clear" @mouseenter="show_sort">
        <h2 class="all">全部商品分类</h2>
        <!-- 过渡动画 -->
        <transition name="sort">
            <!-- 三级联动 -->
          <div class="sort" v-show="show">
              <!-- 一级分类 -->
              <div class="all-sort-list2" @click="goSearch">
                  <div
                      class="item"
                      :class="{current:currentIndex == index}"
                      v-for="(c1, index) in categoryList"
                      :key="c1.categoryId"
                  >
                      <h3 @mouseenter="change_index(index)" >
                          <!-- 路由跳转 -->
                          <a :data-categoryName="c1.categoryName" :data-category1Id="c1.categoryId">{{ c1.categoryName }}</a>
                      </h3>
                      <!-- 二级分类 -->
                      <div class="item-list clearfix" :style="{display:currentIndex == index?'block':'none'}">
                          <div
                              class="subitem"
                              v-for="(c2, index) in c1.categoryChild"
                              :key="c2.categoryId"
                          >
                              <dl class="fore">
                              <dt>
                                  <!-- 路由跳转 -->
                                  <a :data-categoryName="c2.categoryName" :data-category2Id="c2.categoryId">{{ c2.categoryName }}</a>
                              </dt>
                              <!-- 三级分类 -->
                              <dd>
                                  <em
                                  v-for="(c3, index) in c2.categoryChild"
                                  :key="c3.categoryId"
                                  >
                                      <!-- 路由跳转 -->
                                      <a :data-categoryName="c3.categoryName" :data-category3Id="c3.categoryId">{{ c3.categoryName }}</a>
                                  </em>
                              </dd>
                              </dl>
                          </div>
                      </div>
                  </div>
              </div>
          </div>
        </transition>
      </div>
      <router-view></router-view>
      <nav class="nav">
        <a href="###">服装城</a>
        <a href="###">美妆馆</a>
        <a href="###">尚品汇超市</a>
        <a href="###">全球购</a>
        <a href="###">闪购</a>
        <a href="###">团购</a>
        <a href="###">有趣</a>
        <a href="###">秒杀</a>
      </nav>
    </div>
  </div>
</template>

<script> 
import { mapState } from "vuex";
import throttle from 'lodash/throttle';

export default {
  name: "TypeNav",
  data() {
    return {
      // 三级联动id
      currentIndex: -1,
      // 三级联动显示/隐藏
      show:true
    };
  },
  methods: {
    // 节流
    change_index:throttle(function(index){
        this.currentIndex = index
    }, 50),

    // Search页面 三级联动 失去焦点
    clear(){
        this.currentIndex = -1
        if(this.$route.path == '/search'){
          this.show = false
        }
    },
    // 跳转至Search组件并传参
    goSearch(event){
        // 重置搜索框
        this.$store.dispatch("keyword_actions", '')
        
        let {categoryname, category1id, category2id, category3id} = event.target.dataset

        if(categoryname){
            // 预处理路由跳转参数
            let location = {
                name:'Search'
            }
            let query = {
                categoryName:categoryname
            }

            if(category1id){  // 一级分类跳转
                query.category1Id = category1id
            }else if(category2id){  // 二级分类跳转
                query.category2Id = category2id
            }else{  // 三级分类跳转
                query.category3Id = category3id
            }

            // 合并参数
            if(this.$route.params){
              location.params = this.$route.params
            }
            location.query = query
            this.$router.push(location)
        }
    },
    // Search页面 三级联动 获得焦点
    show_sort(){
      this.show = true
    }
  },
  mounted() {
    // Search页面 三级联动 初始化焦点
    if(this.$route.path == '/search'){
      this.show = false
    }
  },
  computed: {
    // 获取 三级联动 接口数据
    ...mapState({
      categoryList: (state) => {
        return state.home.categoryList;
      },
    }),
  },
};
</script>

<style lang="less" scoped>
.type-nav {
  border-bottom: 2px solid #e1251b;

  .container {
    width: 1200px;
    margin: 0 auto;
    display: flex;
    position: relative;

    .all {
      width: 210px;
      height: 45px;
      background-color: #e1251b;
      line-height: 45px;
      text-align: center;
      color: #fff;
      font-size: 14px;
      font-weight: bold;
    }

    .nav {
      a {
        height: 45px;
        margin: 0 22px;
        line-height: 45px;
        font-size: 16px;
        color: #333;
      }
    }

    .sort {
      position: absolute;
      left: 0;
      top: 45px;
      width: 210px;
      height: 461px;
      position: absolute;
      background: #fafafa;
      z-index: 999;

      .all-sort-list2 {
        .item {
          h3 {
            line-height: 30px;
            font-size: 14px;
            font-weight: 400;
            overflow: hidden;
            padding: 0 20px;
            margin: 0;

            a {
              color: #333;
            }
          }

          .item-list {
            display: none;
            position: absolute;
            width: 734px;
            min-height: 460px;
            background: #f7f7f7;
            left: 210px;
            border: 1px solid #ddd;
            top: 0;
            z-index: 9999 !important;

            .subitem {
              float: left;
              width: 650px;
              padding: 0 4px 0 8px;

              dl {
                border-top: 1px solid #eee;
                padding: 6px 0;
                overflow: hidden;
                zoom: 1;

                &.fore {
                  border-top: 0;
                }

                dt {
                  float: left;
                  width: 54px;
                  line-height: 22px;
                  text-align: right;
                  padding: 3px 6px 0 0;
                  font-weight: 700;
                }

                dd {
                  float: left;
                  width: 415px;
                  padding: 3px 0 0;
                  overflow: hidden;

                  em {
                    float: left;
                    height: 14px;
                    line-height: 14px;
                    padding: 0 8px;
                    margin-top: 5px;
                    border-left: 1px solid #ccc;
                  }
                }
              }
            }
          }

        //   &:hover {
        //     .item-list {
        //       display: block;
        //     }
        //   }
        }
        .current {
            background-color: skyblue;
        }
      }
    }
    .sort-enter{
      height: 0px;
    }
    .sort-enter-to{
      height: 461px;
    }
    .sort-enter-active{
      transition: all .5s linear;
    }
  }
}
</style>