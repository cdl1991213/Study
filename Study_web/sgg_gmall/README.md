# sgg_gmall

## Project setup
```
npm install
```

### Compiles and hot-reloads for development
```
npm run serve
```

### Compiles and minifies for production
```
npm run build
```

### Lints and fixes files
```
npm run lint
```

### Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).

## 项目目录
- node_modules  项目依赖文件夹
- public    静态资源，webpack进行打包时，会原封不动的打包到dist文件夹
- src   源代码文件
  - assets  公用的静态资源，webpack进行打包时，会把静态资源当作一个模块，打包到JS文件里
  - components  非路由组件
  - pages   路由组件
  - router  配置路由
  - APP.vue 根组件
  - main.js 程序入口文件
- babel.config.js babel相关配置文件
- package.json  包记录文件
- package.json  包缓存性文件

## 项目实战笔记
### 项目搭建流程
1. Vue-cli脚手架初始化项目文件
2. 修改配置
    serve自动打开浏览器(package.json)
    关闭eslint校验(vue.config.js)
    配置src文件夹别名(jsconfig.json)
3. 确定css预处理器，本项目为less
   安装less less-loader包
   `<style lang="less" scoped>`
4. 前台路由分析
    安装vue-router包
    上中下结构
    路由组件------------------------------------------------------(pages)
      1. home首页路由组件
            1. TypeNav商品分类导航
            2. ListContainer列表
            3. Recommend今日推荐
            4. Rank商品排行
            5. Like猜你喜欢
            6. Floor楼层
            7. Brand商标
      2. search搜索路由组件
            1. SearchSelector搜索筛选器
      3. login登录路由组件
      4. register注册路由组件
    非路由组件------------------------------------------------------(components)
      5. header头部
      6. footer(注册于home search组件)底部
      7. typeNav三级联动
      8. carousel轮播图
5. 静态页面构建
6. mock数据------------------------------------------------------(mock)
7. 动态获取服务器数据------------------------------------------------------(api)
      1. 二次封装axios
      2. 配置代理服务器
8. vuex模块式开发------------------------------------------------------(store)
9. 组件获取store仓库数据，动态展示数据
10. 插件开发
   1. 轮播图--swiper@5
   

### 所遇问题
1. 依赖包版本
   本项目使用Vue2语法，vue-cli版本需对应Vue2，less版本为5，vue-router版本为3, vuex版本为3
   
2. 编程式路由导航，重复跳转报错
   原因：版本问题
   解决办法：
        1. 使用旧版本vue-router
        2. 跳转路径后，catch捕获异常，不做处理
        3. 在router配置文件中VueRouter上配置全局路由跳转。重写VueRouter.prototype.push 方法，使用 catch 方法捕获错误。如果路由跳转失败，不会在控制台输出错误信息，而是静默处理
   
3. 浏览器卡顿现象（只执行部分事件的回调函数）
   解决办法：通过lodash插件实现防抖（_.debounce()函数）、节流(_.throttle()函数)

4. 路由跳转的方式：声明式导航(router-link)、编程式导航。
   大量的声明式导航，导致页面存在大量router-link
   编程式导航+事件委派（将事件绑定在父元素）需要判断：a.点击的对象是否为目标对象    b.获取点击对象的数据

5. mock数据
   1. 在项目中的src文件夹内创建mock文件夹
   2. 准备JSON数据【在mock文件夹中创建JSON文件,JSON文件内容需要格式化，不允许含有空格】
   3. 将mock数据需要的图片放到public文件夹【public文件夹在打包时，资源会原封不动的打包到dist文件夹】
   4. mock.js模块实现mock数据(mockServe.js)