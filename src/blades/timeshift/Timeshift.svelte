<script lang="ts">
  import { onMount } from "svelte";

  let people = $state<{ name: string; timezone: string }[]>([]);
  let time = $state("");

  onMount(() => {
    const interval = setInterval(() => {
      time = new Date().toLocaleTimeString("en-US");
    }, 1000);
  });
</script>

<p>{time}</p>
