import { type FC, type ReactNode } from "react";

// ── Design tokens ──

const inputBase =
  "w-full px-3 py-2 bg-white border border-[#E8E7E3] rounded-lg " +
  "text-sm text-[#171717] placeholder:text-[#C5C3BB] " +
  "focus:outline-none focus:border-[#1E1E3F] focus:ring-2 focus:ring-[#1E1E3F]/10 " +
  "disabled:opacity-40 disabled:cursor-not-allowed disabled:bg-[#FAFAF8] " +
  "transition-colors duration-150";

const labelClass =
  "block text-xs font-medium text-[#525252] mb-1.5 tracking-wide";

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
      focus:outline-none focus:ring-2 focus:ring-[#1E1E3F]/20 focus:ring-offset-2 focus:ring-offset-white
      disabled:opacity-40 disabled:cursor-not-allowed
      ${checked ? "bg-[#1E1E3F]" : "bg-[#E8E7E3] hover:bg-[#DDDCD7]"}`}
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
    <span className="text-sm text-[#525252] select-none">{label}</span>
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
    {hint && <p className="mt-1 text-xs text-[#A3A3A3]">{hint}</p>}
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
    {hint && <p className="mt-1 text-xs text-[#A3A3A3]">{hint}</p>}
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
    className={`bg-white rounded-xl shadow-[0_1px_3px_rgba(0,0,0,0.02),0_8px_32px_rgba(0,0,0,0.03)] ring-1 ring-black/[0.03] p-6 ${className}`}
  >
    {children}
  </div>
);

// ── SectionHeader — just a title, no badge ──

export const SectionHeader: FC<{ title: string }> = ({ title }) => (
  <h2 className="text-[15px] font-semibold text-[#171717] tracking-tight">{title}</h2>
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
        ? "bg-[#F5F4F1] text-[#A3A3A3]"
        : "bg-[#1E1E3F] text-white hover:bg-[#2D2D5E] active:scale-[0.98]"
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
      bg-white text-[#525252] border border-[#E8E7E3] hover:bg-[#FAFAF8] hover:text-[#171717] active:scale-[0.98]
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
  <div className="flex items-center gap-3 px-4 py-2.5 bg-red-50/80 border border-red-100 rounded-lg text-sm text-red-600">
    <span className="flex-1">{message}</span>
    <button
      onClick={onDismiss}
      className="text-red-400 hover:text-red-600 transition-colors text-base leading-none"
    >
      ×
    </button>
  </div>
);
