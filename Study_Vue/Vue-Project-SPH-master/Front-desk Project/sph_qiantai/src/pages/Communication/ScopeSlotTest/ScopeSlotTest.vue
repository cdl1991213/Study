<template>
  <div>
    <h1>作用域插槽</h1>
    <List :todos="todos">
         <template v-slot="{todo,$index}">
             <h1 :style="{color:todo.isComplete?'red':'cyan'}">{{todo.text}}----{{$index}}</h1>
         </template>
    </List>
  </div>
</template>

<script type="text/ecmascript-6">
  import List from './List'
  export default {
    name: 'ScopeSlotTest',
    data () {
      return {
        todos: [
          {id: 1, text: 'AAA', isComplete: false},
          {id: 2, text: 'BBB', isComplete: true},
          {id: 3, text: 'CCC', isComplete: false},
          {id: 4, text: 'DDD', isComplete: false},
        ]
      }
    },

    components: {
      List,
    }
  }
</script>
