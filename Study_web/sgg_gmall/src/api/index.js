// api接口统一管理
import requests from "./requests";
import requests_mock from "./requestsMock";

/* Home模块接口 */
// 三级联动
export const reqCategoryList = () => {
  // 发送请求，返回promise对象
  return requests({
    url: "product/getBaseCategoryList",
    method: "get",
  });
};

// banner轮播图
export const reqBannerList = () => {
  return requests_mock({
    url: "/banner",
    method: "get",
  });
};

// floor列表
export const reqFloorList = () => {
  return requests_mock({
    url: "/floor",
    method: "get",
  });
};

/* Search模块接口 */
// Search搜索
export const reqSearchList = (params) => {
  return requests({
    url:"/list",
    method:"post",
    data:params
  })
}