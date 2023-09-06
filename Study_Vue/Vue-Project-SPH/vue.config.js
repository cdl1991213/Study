const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  // 关闭ESLint校验
  lintOnSave:false,
  // 代理服务器(解决跨域)
  devServer:{
    proxy:{
      "/api":{
        target:"http://gmall-h5-api.atguigu.cn",
        
        // 将/api替换成空字符串
        // pathRewrite:{
        //   '^/api':''
        // },
        
        changeOrigin: true //开启代理：在本地会创建一个虚拟服务端
      }
    }
  }
})

