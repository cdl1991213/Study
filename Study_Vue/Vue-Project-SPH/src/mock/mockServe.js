import Mock from 'mockjs'
import banner from './banner.json';
import floor from './floor.json';

/* 
 mock数据 
 参数1：请求地址
 参数2：请求数据
*/
// 轮播图数据
Mock.mock("/mock/banner", {code:200, data:banner})
// 底部数据
Mock.mock("/mock/floor", {code:200, data:floor}) 