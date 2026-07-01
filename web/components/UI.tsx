import { useState, useEffect, type FC } from "react";

const inputBase =
  "w-full px-3 py-2 bg-ctp-base border border-ctp-surface0 rounded-lg " +
  "text-sm text-ctp-text placeholder:text-ctp-overlay1 " +
  "focus:outline-none focus:border-ctp-pink focus:ring-2 focus:ring-ctp-pink/15 " +
  "disabled:opacity-40 disabled:cursor-not-allowed disabled:bg-ctp-surface0 " +
  "transition-colors duration-150";

const labelClass =
  "block text-xs font-medium text-ctp-subtext0 mb-1.5 tracking-wide";

export function useConfigSection<T>(config: T, onChange: (c: T) => void) {
  const [local, setLocal] = useState<T>(config);

  useEffect(() => {
    setLocal(config);
  }, [config]);

  const update = (patch: Partial<T>) => {
    const next = { ...local, ...patch };
    setLocal(next);
    onChange(next);
  };

  return [local, update] as const;
}

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
    className={`focus:ring-ctp-pink/20 focus:ring-offset-ctp-mantle relative inline-flex h-5 w-9 items-center rounded-full transition-colors duration-150 focus:ring-2 focus:ring-offset-2 focus:outline-none disabled:cursor-not-allowed disabled:opacity-40 ${checked ? "bg-ctp-pink" : "bg-ctp-surface0 hover:bg-ctp-surface1"}`}
  >
    <span
      className={`inline-block h-3.5 w-3.5 transform rounded-full bg-white shadow-sm transition-transform duration-150 ease-out ${checked ? "translate-x-5" : "translate-x-0.5"}`}
    />
  </button>
);

export const ToggleRow: FC<{
  label?: string;
  checked: boolean;
  onChange: (v: boolean) => void;
  disabled?: boolean;
}> = ({ label, checked, onChange, disabled }) => (
  <div
    className={`flex items-center py-1 ${label ? "justify-between" : "justify-end"}`}
  >
    {label && (
      <span className="text-ctp-subtext0 text-sm select-none">{label}</span>
    )}
    <Toggle checked={checked} onChange={onChange} disabled={disabled} />
  </div>
);

export const Input: FC<{
  label: string;
  value: string;
  onChange: (v: string) => void;
  placeholder?: string;
  type?: string;
  disabled?: boolean;
  hint?: string;
  mono?: boolean;
}> = ({
  label,
  value,
  onChange,
  placeholder,
  type = "text",
  disabled,
  hint,
  mono,
}) => (
  <div>
    <label className={labelClass}>{label}</label>
    <input
      type={type}
      value={value}
      onChange={(e) => onChange(e.target.value)}
      disabled={disabled}
      placeholder={placeholder}
      className={`${inputBase}${mono ? "font-mono" : ""}`}
    />
    {hint && <p className="text-ctp-overlay1 mt-1 text-xs">{hint}</p>}
  </div>
);

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

export const SectionHeader: FC<{ title: string }> = ({ title }) => (
  <h2 className="text-ctp-text text-[15px] font-semibold tracking-tight">
    {title}
  </h2>
);

export const SaveButton: FC<{
  onClick: () => void;
  saving: boolean;
  saved: boolean;
  label?: string;
}> = ({ onClick, saving, saved, label = "Save Changes" }) => (
  <button
    onClick={onClick}
    disabled={saving || saved}
    className={`rounded-full px-3.5 py-2 text-[13px] font-medium transition-all duration-200 ${
      saved
        ? "bg-ctp-surface0 text-ctp-overlay1"
        : "bg-ctp-pink text-ctp-base hover:bg-ctp-pink/85 shadow-sm"
    } disabled:cursor-not-allowed`}
  >
    {saved ? "Saved" : saving ? "Saving..." : label}
  </button>
);

export const RestartButton: FC<{
  onClick: () => void;
  restarting: boolean;
  label?: string;
}> = ({ onClick, restarting, label = "Restart" }) => (
  <button
    onClick={onClick}
    disabled={restarting}
    className={`text-ctp-subtext0 hover:text-ctp-text hover:bg-ctp-surface0 rounded-full px-3.5 py-2 text-[13px] font-medium transition-all duration-200 disabled:cursor-not-allowed disabled:opacity-40`}
  >
    {restarting ? "Restarting..." : label}
  </button>
);

export const ErrorBar: FC<{ message: string; onDismiss: () => void }> = ({
  message,
  onDismiss,
}) => (
  <div className="bg-ctp-red/10 border-ctp-red/20 text-ctp-red flex items-center gap-3 rounded-lg border px-4 py-2.5 text-sm">
    <span className="flex-1">{message}</span>
    <button
      onClick={onDismiss}
      className="text-ctp-red/60 hover:text-ctp-red text-base leading-none transition-colors"
    >
      ×
    </button>
  </div>
);
