<script lang="ts">
  import { onMount } from "svelte";
  import { invoke } from "@tauri-apps/api/core";

  let countries = $state<[string, string][]>([]);
  let selectedCountry = $state("");
  let age = $state(0);
  let score = $state(-1);
  let time = $state("");

  async function loadCountries() {
    countries = await invoke("list_countries");
  }

  async function getScore() {
    if (!selectedCountry || !age) return;
    score = await invoke("score_for_person", {
      countryCode: selectedCountry,
      age,
      workStart: -1,
      workEnd: -1,
      overrideStart: -1,
      overrideEnd: -1,
    });
  }

  onMount(() => {
    loadCountries();
    const interval = setInterval(() => {
      time = new Date().toLocaleTimeString("en-US");
      getScore();
    }, 1000);
  });
</script>

<div>
  <select bind:value={selectedCountry}>
    <option value="">pick a country</option>
    {#each countries as [code, name]}
      <option value={code}>{name}</option>
    {/each}
  </select>

  <input type="number" bind:value={age} placeholder="age" min="1" max="120" />

  <p>{time}</p>
  {#if score >= 0}
    <p>{score}/100</p>
  {/if}
</div>
