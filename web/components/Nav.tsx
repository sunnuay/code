import { tabs } from "./Types";
import { SaveButton, RestartButton } from "./UI";

interface Props {
  activeTab: string;
  onTabChange: (id: string) => void;
  onSave: () => void;
  onRestart: () => void;
  saving: boolean;
  saved: boolean;
  restarting: boolean;
}

export const Nav = ({
  activeTab,
  onTabChange,
  onSave,
  onRestart,
  saving,
  saved,
  restarting,
}: Props) => (
  <div className="border-ctp-surface0 flex items-center justify-between border-b px-5 pt-4 pb-3">
    <nav className="flex items-center gap-1">
      {tabs.map(({ id, name }) => {
        const active = activeTab === id;
        return (
          <button
            key={id}
            onClick={() => onTabChange(id)}
            className={`rounded-full px-3.5 py-2 text-[13px] font-medium transition-all duration-200 ${
              active
                ? "bg-ctp-pink text-ctp-base shadow-sm"
                : "text-ctp-subtext0 hover:text-ctp-text hover:bg-ctp-surface0"
            }`}
          >
            {name}
          </button>
        );
      })}
    </nav>
    <div className="flex items-center gap-2">
      <RestartButton onClick={onRestart} restarting={restarting} />
      <SaveButton onClick={onSave} saving={saving} saved={saved} label="Save" />
    </div>
  </div>
);
