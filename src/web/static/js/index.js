const socket = io();


const { createApp } = Vue

createApp({

compilerOptions: {
    delimiters: ["[[", "]]"]
    },


  data() {
    return {
      socket: null,
      temperature: '',
      bright: ''
    }
  },

  created() {
    this.socket = io()

    this.socket.on('oficina/reuniones/luz/brillo', data => {
        this.temperature = data.data
    })
    
    this.socket.on('oficina/servidores/servidor1/temperatura', data => {
        this.bright = data.data
    })

  }


}).mount('#app')



