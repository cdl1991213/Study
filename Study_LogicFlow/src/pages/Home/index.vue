<template>
    <div>
        Hello HUNDSUN!
        <button @click="showOptionPopup">打开选项选择框</button>
        <OptionPopup
            :selectOptions="selectOptions"
            ref="optionpopup"
            v-show="optionPopupisShow"
        />
    </div>
</template>
  
<script>
import OptionPopup from "@/components/OptionPopup";

export default {
    name: "Home",
    components: {
        OptionPopup,
    },
    data() {
        return {
            // 选项选择框是否显示
            optionPopupisShow: false,
            selectOptions: [
                { label: "选项1", value: "option1" },
                { label: "选项2", value: "option2" },
                { label: "选项3", value: "option3" },
            ],
        };
    },
    mounted() {
        this.$refs.optionpopup.$on("hideOptionPopup", this.hideOptionPopup);
    },
    methods: {
        showOptionPopup() {
            this.optionPopupisShow = true;
        },
        hideOptionPopup() {
            this.optionPopupisShow = false;
        },
    },
};
</script>
  
<style scoped>
</style>