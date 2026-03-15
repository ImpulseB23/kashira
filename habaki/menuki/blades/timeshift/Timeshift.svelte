<script lang="ts">
  import { onMount } from "svelte";
  import { invoke } from "@tauri-apps/api/core";

  type CountryInfo = { code: string; name: string; timezones: string[] };

  let countries = $state<CountryInfo[]>([]);
  let selectedCountry = $state("");
  let selectedTimezone = $state("");
  let age = $state<number | null>(null);
  let score = $state(-1);
  let localTime = $state("");

  let timezones = $derived(
    countries.find((c) => c.code === selectedCountry)?.timezones ?? []
  );

  async function loadCountries() {
    countries = await invoke("list_countries");
  }

  async function update() {
    if (!selectedCountry || age === null || age < 1 || !selectedTimezone) return;

    score = await invoke("score_for_person", {
      countryCode: selectedCountry,
      timezone: selectedTimezone,
      age,
      workStart: -1,
      workEnd: -1,
      overrideStart: -1,
      overrideEnd: -1,
    });

    if (selectedTimezone) {
      localTime = new Date().toLocaleTimeString("en-US", {
        timeZone: selectedTimezone,
        hour: "2-digit",
        minute: "2-digit",
      });
    }
  }

  onMount(() => {
    loadCountries();
    const timer = setInterval(update, 1000);
    return () => clearInterval(timer);
  });
</script>

<div class="timeshift">
  <div class="inputs">
    <select bind:value={selectedCountry} onchange={() => {
      selectedTimezone = timezones.length === 1 ? timezones[0] : "";
      update();
    }}>
      <option value="">country</option>
      {#each countries as c}
        <option value={c.code}>{c.name}</option>
      {/each}
    </select>

    {#if timezones.length > 1}
      <select bind:value={selectedTimezone} onchange={() => update()}>
        <option value="">timezone</option>
        {#each timezones as tz}
          <option value={tz}>{tz.split("/").pop()?.replace(/_/g, " ")}</option>
        {/each}
      </select>
    {/if}

    <input
      type="number"
      bind:value={age}
      placeholder="age"
      min="1"
      max="120"
      oninput={() => update()}
    />
  </div>

  {#if score >= 0}
    <div class="result">
      {#if localTime}
        <p class="time">{localTime}</p>
      {/if}
      <p class="score">{score}<span class="max">/100</span></p>
    </div>
  {/if}
</div>

<style>
  .timeshift {
    padding: 16px;
  }

  .inputs {
    display: flex;
    flex-direction: column;
    gap: 8px;
  }

  select, input {
    padding: 8px 12px;
    border: 1px solid var(--border);
    border-radius: 6px;
    background: var(--surface);
    color: var(--text);
    font-size: 14px;
    outline: none;
  }

  select:focus, input:focus {
    border-color: var(--sakura);
  }

  .result {
    margin-top: 32px;
    text-align: center;
  }

  .time {
    font-size: 18px;
    color: var(--text-muted);
    margin: 0;
  }

  .score {
    font-size: 48px;
    font-weight: bold;
    margin: 8px 0;
    color: var(--sakura);
  }

  .max {
    font-size: 20px;
    color: var(--text-dim);
  }
</style>
