<script lang="ts">
  import { getCurrentWindow } from "@tauri-apps/api/window";

  const win = getCurrentWindow();
</script>

<div class="titlebar" data-tauri-drag-region>
  <div class="drag" data-tauri-drag-region></div>
  <div class="controls">
    <button onclick={() => win.minimize()} aria-label="minimize">
      <svg width="12" height="12" viewBox="0 0 12 12"><line x1="2" y1="6" x2="10" y2="6" stroke="currentColor" stroke-width="1"/></svg>
    </button>
    <button onclick={() => win.toggleMaximize()} aria-label="maximize">
      <svg width="12" height="12" viewBox="0 0 12 12"><rect x="2" y="2" width="8" height="8" stroke="currentColor" fill="none" stroke-width="1"/></svg>
    </button>
    <button class="close" onclick={() => win.close()} aria-label="close">
      <svg width="12" height="12" viewBox="0 0 12 12"><line x1="2" y1="2" x2="10" y2="10" stroke="currentColor" stroke-width="1.2"/><line x1="10" y1="2" x2="2" y2="10" stroke="currentColor" stroke-width="1.2"/></svg>
    </button>
  </div>
</div>

<style>
  .titlebar {
    display: flex;
    align-items: center;
    justify-content: space-between;
    height: 28px;
    background: var(--surface);
    user-select: none;
    -webkit-user-select: none;
    border-bottom: 1px solid var(--border);
  }

  .drag {
    flex: 1;
    height: 100%;
  }

  .controls {
    display: flex;
    height: 100%;
  }

  button {
    background: none;
    border: none;
    color: var(--text-dim);
    width: 46px;
    height: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
    padding: 0;
  }

  button:hover {
    background: rgba(255, 255, 255, 0.06);
    color: var(--text);
  }

  .close:hover {
    background: #e81123;
    color: white;
  }
</style>
