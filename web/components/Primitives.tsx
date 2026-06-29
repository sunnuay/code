import type { FC, ReactNode } from "react";
import { RefreshCw } from "lucide-react";

const inputBase =
  "w-full px-3 py-2 bg-white border border-gray-200 rounded-md text-sm text-black placeholder:text-gray-400 focus:outline-none focus:border-black focus:ring-1 focus:ring-black disabled:bg-gray-50 disabled:text-gray-400 transition-colors";

const btnPrimary =
  "inline-flex items-center px-3.5 py-2 bg-black text-white text-sm font-medium rounded-md hover:bg-gray-800 disabled:opacity-40 disabled:cursor-not-allowed transition-colors";

const labelClass = "block text-xs font-medium text-gray-500 mb-1.5 uppercase tracking-wider";

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
    className={`relative inline-flex h-5 w-9 items-center rounded-full transition-colors focus:outline-none focus:ring-2 focus:ring-black focus:ring-offset-2 disabled:opacity-40 ${
      checked ? "bg-black" : "bg-gray-300"
    }`}
  >
    <span
      className={`inline-block h-3.5 w-3.5 transform rounded-full bg-white transition-transform ${
        checked ? "translate-x-5" : "translate-x-0.5"
      }`}
    />
  </button>
);

export const ToggleRow: FC<{
  label: string;
  checked: boolean;
  onChange: (v: boolean) => void;
  disabled?: boolean;
}> = ({ label, checked, onChange, disabled }) => (
  <div className="flex items-center gap-3">
    <label className="text-sm font-medium text-gray-700">{label}</label>
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
    {hint && <p className="text-xs text-gray-400 mt-1">{hint}</p>}
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
      className={inputBase}
    />
  </div>
);

export const SaveButton: FC<{
  saving: boolean;
  onClick: () => void;
  label?: string;
}> = ({ saving, onClick, label = "保存配置" }) => (
  <button onClick={onClick} disabled={saving} className={btnPrimary}>
    <RefreshCw size={14} className={`mr-1.5 ${saving ? "animate-spin" : ""}`} />
    {saving ? "保存中..." : label}
  </button>
);

export const Card: FC<{ children: ReactNode; className?: string }> = ({
  children,
  className = "",
}) => (
  <div className={`bg-white border border-gray-100 rounded-lg ${className}`}>
    {children}
  </div>
);

export const CardHeader: FC<{ title: string; status?: { enabled: boolean } }> = ({
  title,
  status,
}) => (
  <div className="flex justify-between items-center mb-6">
    <h2 className="text-lg font-semibold text-black">{title}</h2>
    {status && (
      <span className="px-2.5 py-0.5 text-xs rounded-full border border-gray-200 text-gray-500">
        {status.enabled ? "已启用" : "已停用"}
      </span>
    )}
  </div>
);
