<template>
    <div class="modal-wrapper">
        <div class="modal-overlay"></div>
        <div class="modal-content">
            this is OptionPopup
            <select v-model="selectedOption">
                <option
                    v-for="(option, index) in selectOptions"
                    :key="index"
                    :value="option.value"
                >
                    {{ option.label }}
                </option>
            </select>
            <button @click="enterBusinessProcessConfigurationPage">确认</button>
            <button @click="hideOptionPopup">关闭</button>
        </div>
    </div>
</template>
  
  <script>
export default {
    name: "OptionPopup",
    props: {
        selectOptions: {
            type: Array,
            required: true,
        },
    },
    data() {
        return {
            selectedOption: null,
        };
    },
    methods: {
        hideOptionPopup() {
            this.$emit("hideOptionPopup");
        },
        enterBusinessProcessConfigurationPage() {
            // 请求数据
            switch (this.selectedOption) {
                case "option1":
                    this.$store.dispatch("businessProcessTemplate1_actions").then(() => {
                        this.toBusinessProcessConfigurationPage()
                    });
                    break
                case "option2":
                    this.$store.dispatch("businessProcessTemplate2_actions").then(() => {
                        this.toBusinessProcessConfigurationPage()
                    });
                    break
                case "option3":
                    alert('当前流程模板未配置')
                    break
            }
        },
        toBusinessProcessConfigurationPage(){
            // 路由跳转
            let location = {
                name: "BusinessProcessConfiguration",
            };
            let query = {
                selectedOption: this.selectedOption,
            };
            location.query = query;
            this.$router.push(location);
        },
    },
};
</script>
  
  <style scoped>
.modal-wrapper {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    z-index: 1000;
}

.modal-overlay {
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.5);
    z-index: -1;
}

.modal-content {
    background-color: white;
    padding: 20px;
    border-radius: 5px;
    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
}

select,
button {
    margin-top: 10px;
}
</style>
  