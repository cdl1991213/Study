<template>
  <div class="swiper-container" ref="mySwiper">
    <div class="swiper-wrapper">
      <div
        class="swiper-slide"
        v-for="(carousel, index) in carouselList"
        :key="carousel.id"
      >
        <img :src="carousel.imgUrl" />
      </div>
    </div>
    <!-- 如果需要分页器 -->
    <div class="swiper-pagination"></div>

    <!-- 如果需要导航按钮 -->
    <div class="swiper-button-prev"></div>
    <div class="swiper-button-next"></div>
  </div>
</template>

<script>
import Swiper from "swiper";
export default {
  name: "Carousel",
  props: ["carouselList"],
  watch: {
    carouselList: {
      // 立即监听，触发handler
      immediate: true,
      // 监听触发
      handler(newValue, oldValue) {
        this.$nextTick(() => {
          let mySwiper = new Swiper(this.$refs.mySwiper, {
            loop: true,
            // 分页器
            pagination: {
              el: ".swiper-pagination",
              clickable: true,
            },
            // 导航按钮
            navigation: {
              nextEl: ".swiper-button-next",
              prevEl: ".swiper-button-prev",
            },
          });
        });
      },
    },
  },
};
</script>

<style lang="less" scoped>
</style>