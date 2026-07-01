import { type FC, type ReactNode } from "react";

// ── Design tokens ──

const inputBase =
  "w-full px-3 py-2 bg-ctp-base border border-ctp-surface0 rounded-lg " +
  "text-sm text-ctp-text placeholder:text-ctp-overlay1 " +
  "focus:outline-none focus:border-ctp-pink focus:ring-2 focus:ring-ctp-pink/15 " +
  "disabled:opacity-40 disabled:cursor-not-allowed disabled:bg-ctp-surface0 " +
  "transition-colors duration-150";

const labelClass =
  "block text-xs font-medium text-ctp-subtext0 mb-1.5 tracking-wide";

// ── Toggle ──

export const Toggle: FC<{
  checked: boolean;
  onChange: (v: boolean) => void;
  disabled?: boolean;
}> = ({ checked, onChange, disabled }) => (
  <button
    type="button"
    role="switch"
    aria-checked={checked}
    onClick={() => onChange(!checked)}
    disabled={disabled}
    className={`relative inline-flex h-5 w-9 items-center rounded-full transition-colors duration-150
      focus:outline-none focus:ring-2 focus:ring-ctp-pink/20 focus:ring-offset-2 focus:ring-offset-ctp-mantle
      disabled:opacity-40 disabled:cursor-not-allowed
      ${checked ? "bg-ctp-pink" : "bg-ctp-surface0 hover:bg-ctp-surface1"}`}
  >
    <span
      className={`inline-block h-3.5 w-3.5 transform rounded-full bg-white shadow-sm
        transition-transform duration-150 ease-out
        ${checked ? "translate-x-5" : "translate-x-0.5"}`}
    />
  </button>
);

// ── ToggleRow ──

export const ToggleRow: FC<{
  label: string;
  checked: boolean;
  onChange: (v: boolean) => void;
  disabled?: boolean;
}> = ({ label, checked, onChange, disabled }) => (
  <div className="flex items-center justify-between py-1">
    <span className="text-sm text-ctp-subtext0 select-none">{label}</span>
    <Toggle checked={checked} onChange={onChange} disabled={disabled} />
  </div>
);

// ── Input ──

export const Input: FC<{
  label: string;
  value: string;
  onChange: (v: string) => void;
  placeholder?: string;
  type?: string;
  disabled?: boolean;
  hint?: string;
}> = ({ label, value, onChange, placeholder, type = "text", disabled, hint }) => (
  <div>
    <label className={labelClass}>{label}</label>
    <input
      type={type}
      value={value}
      onChange={(e) => onChange(e.target.value)}
      disabled={disabled}
      placeholder={placeholder}
      className={inputBase}
    />
    {hint && <p className="mt-1 text-xs text-ctp-overlay1">{hint}</p>}
  </div>
);

// ── MonoInput ──

export const MonoInput: FC<{
  label: string;
  value: string;
  onChange: (v: string) => void;
  placeholder?: string;
  type?: string;
  disabled?: boolean;
  hint?: string;
}> = ({ label, value, onChange, placeholder, type = "text", disabled, hint }) => (
  <div>
    <label className={labelClass}>{label}</label>
    <input
      type={type}
      value={value}
      onChange={(e) => onChange(e.target.value)}
      disabled={disabled}
      placeholder={placeholder}
      className={`${inputBase} font-mono text-sm`}
    />
    {hint && <p className="mt-1 text-xs text-ctp-overlay1">{hint}</p>}
  </div>
);

// ── NumberInput ──

export const NumberInput: FC<{
  label: string;
  value: number;
  onChange: (v: number) => void;
  placeholder?: string;
  min?: number;
  disabled?: boolean;
}> = ({ label, value, onChange, placeholder, min, disabled }) => (
  <div>
    <label className={labelClass}>{label}</label>
    <input
      type="number"
      value={value}
      onChange={(e) => onChange(parseInt(e.target.value) || 0)}
      disabled={disabled}
      placeholder={placeholder}
      min={min}
      className={`${inputBase} font-mono`}
    />
  </div>
);

// ── Card — refined, modern ──

export const Card: FC<{ children: ReactNode; className?: string }> = ({
  children,
  className = "",
}) => (
  <div
    className={`bg-ctp-mantle rounded-xl shadow-[0_1px_3px_rgba(0,0,0,0.02),0_8px_32px_rgba(0,0,0,0.03)] ring-1 ring-ctp-crust/50 p-6 ${className}`}
  >
    {children}
  </div>
);

// ── SectionHeader — just a title, no badge ──

export const SectionHeader: FC<{ title: string }> = ({ title }) => (
  <h2 className="text-[15px] font-semibold text-ctp-text tracking-tight">{title}</h2>
);

// ── SaveButton ──

export const SaveButton: FC<{
  onClick: () => void;
  saving: boolean;
  saved: boolean;
  label?: string;
}> = ({ onClick, saving, saved, label = "Save Changes" }) => (
  <button
    onClick={onClick}
    disabled={saving || saved}
    className={`px-3.5 py-1.5 rounded-lg text-xs font-medium transition-all duration-150 ${
      saved
        ? "bg-ctp-surface0 text-ctp-overlay1"
        : "bg-ctp-pink text-ctp-base hover:bg-ctp-pink/85 active:scale-[0.98]"
    } disabled:cursor-not-allowed`}
  >
    {saved ? "Saved" : saving ? "Saving..." : label}
  </button>
);

// ── RestartButton — outline style, same size ──

export const RestartButton: FC<{
  onClick: () => void;
  restarting: boolean;
  label?: string;
}> = ({ onClick, restarting, label = "Restart" }) => (
  <button
    onClick={onClick}
    disabled={restarting}
    className={`px-3.5 py-1.5 rounded-lg text-xs font-medium transition-all duration-150
      bg-ctp-base text-ctp-subtext0 border border-ctp-surface0 hover:bg-ctp-surface0 hover:text-ctp-text active:scale-[0.98]
      disabled:opacity-40 disabled:cursor-not-allowed`}
  >
    {restarting ? "Restarting..." : label}
  </button>
);

// ── ErrorBar ──

export const ErrorBar: FC<{ message: string; onDismiss: () => void }> = ({
  message,
  onDismiss,
}) => (
  <div className="flex items-center gap-3 px-4 py-2.5 bg-ctp-red/10 border border-ctp-red/20 rounded-lg text-sm text-ctp-red">
    <span className="flex-1">{message}</span>
    <button
      onClick={onDismiss}
      className="text-ctp-red/60 hover:text-ctp-red transition-colors text-base leading-none"
    >
      ×
    </button>
  </div>
);
