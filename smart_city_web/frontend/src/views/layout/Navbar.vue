<template>
  <nav>

    <v-app-bar color="dark" class="flex-grow-0" app dark>
      <v-app-bar-nav-icon @click="nav_drawer = !nav_drawer"></v-app-bar-nav-icon>
      <v-img
          class="mx-2"
          src="@/assets/logo.png"
          max-height="40"
          max-width="40"
          contain
      ></v-img>
      <v-toolbar-title class="text-uppercase text--darken-4">
        <span>EDDI Robot Academy</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn v-if="isAuthenticated == true" text color="grey" v-on:click="resign">
        <span>회원 탈퇴</span>
        <v-icon right>mdi-login</v-icon>
      </v-btn>
      <v-btn text color="grey" onclick="location.href='http://localhost:8081/sign-up'">
        <span>Sign Up</span>
        <v-icon right>mdi-account-plus-outline</v-icon>
      </v-btn>
      <v-btn v-if="isAuthenticated == false" text color="grey" onclick="location.href='http://localhost:8081/sign-in'">
        <span>Sign In</span>
        <v-icon right>mdi-login</v-icon>
      </v-btn>
      <v-btn v-else text color="grey" v-on:click="logout">
        <span>Sign Out</span>
        <v-icon right>mdi-exit-to-app</v-icon>
      </v-btn>
    </v-app-bar>

    <v-navigation-drawer app v-model="nav_drawer">
      <v-list-item>
        <v-list-item-content>
          <v-list-item-title class="text-h6">Smart City</v-list-item-title>
          <v-list-item-subtitle>Functions</v-list-item-subtitle>
        </v-list-item-content>
      </v-list-item>
      <v-divider></v-divider>
      <v-list nav dense>
        <v-list-item v-for="link in links" :key="link.name" router :to="link.route">
          <v-list-item-action>
            <v-icon left>
              {{ link.icon }}
            </v-icon>
          </v-list-item-action>
          <v-list-item-content>
            <v-list-item-title>
              {{ link.title }}
            </v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>

  </nav>
</template>

<script>
import {mapState} from "vuex";
import axios from "axios";

export default {
  data() {
    return {
      nav_drawer: false,
      session: false,
      links: [
        { icon: 'mdi-home-outline', title: 'Home', route: '/' },
        { icon: 'mdi-account-alert-outline', title: 'My Page', route: '/my-page' },
        { icon: 'mdi-calendar-check-outline', title: 'Schedule', route: '/schedule' },
        { icon: 'mdi-traffic-light-outline', title: 'Traffic Control', route: '/traffic-control' },
        { icon: 'mdi-car-electric-outline', title: 'Vehicle Control', route: '/vehicle-control' },
        { icon: 'mdi-meter-gas-outline', title: 'Gas Measurement', route: '/air-quality' },
        { icon: 'mdi-lightning-bolt-outline', title: 'Power Plant', route: '/power' },
        { icon: 'mdi-video-wireless-outline', title: 'CCTV', route: '/cctv' },
        { icon: 'mdi-account-group-outline', title: 'Member', route: '/member' },
      ]
    }
  },
  computed: {
    ...mapState(["isAuthenticated"]),
  },
  methods: {
    logout () {
      console.log('getItem: ' + localStorage.getItem("userInfo"))
      //const token = localStorage.getItem("userInfo")
      axios.post("http://localhost:7777/mainpage/logout", localStorage.getItem("userInfo"))
          .then(() => {
            alert("로그아웃 완료");
            localStorage.removeItem("userInfo");
            this.$store.state.isAuthenticated = false;
          })
    },
    resign () {
      let token = localStorage.getItem("userInfo")
      const length = token.length
      console.log('token: ' + token + ', length: ' + length)
      token = token.substr(1, length - 2)
      console.log('token: ' + token)
      axios.post("http://localhost:7777/mainpage/resign", token)
          .then(() => {
            alert("회원탈퇴 완료");
            localStorage.removeItem("userInfo");
            this.$store.state.isAuthenticated = false;
          })
    }
  }
}
</script>