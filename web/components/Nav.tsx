import { tabs } from "./Types";
import { PillButton, SaveButton, RestartButton } from "./UI";

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
      {tabs.map(({ id, name }) => (
        <PillButton
          key={id}
          active={activeTab === id}
          onClick={() => onTabChange(id)}
        >
          {name}
        </PillButton>
      ))}
    </nav>
    <div className="flex items-center gap-2">
      <RestartButton onClick={onRestart} restarting={restarting} />
      <SaveButton onClick={onSave} saving={saving} saved={saved} label="Save" />
    </div>
  </div>
);
