import { Server } from "lucide-react";
import type { LucideIcon } from "lucide-react";

export interface MenuItem {
  id: string;
  name: string;
  icon: LucideIcon;
}

interface SidebarProps {
  menuItems: MenuItem[];
  activeTab: string;
  onTabChange: (id: string) => void;
}

const Sidebar = ({ menuItems, activeTab, onTabChange }: SidebarProps) => (
  <aside className="w-60 bg-white border-r border-gray-100 flex flex-col">
    <div className="h-16 flex items-center px-5 border-b border-gray-100">
      <Server className="text-black mr-2.5" size={20} />
      <h1 className="text-lg font-semibold text-black tracking-tight">
        Proxy Panel
      </h1>
    </div>

    <nav className="flex-1 py-4 px-3 space-y-0.5">
      {menuItems.map((item) => {
        const Icon = item.icon;
        const isActive = activeTab === item.id;
        return (
          <button
            key={item.id}
            onClick={() => onTabChange(item.id)}
            className={`w-full flex items-center px-3 py-2 rounded-md text-sm font-medium transition-colors ${
              isActive
                ? "bg-gray-100 text-black"
                : "text-gray-500 hover:bg-gray-50 hover:text-black"
            }`}
          >
            <Icon size={18} className="mr-2.5" />
            {item.name}
          </button>
        );
      })}
    </nav>

    <div className="p-4 border-t border-gray-100">
      <p className="text-xs text-gray-400 text-center">Proxy Manager v1.0</p>
    </div>
  </aside>
);

export default Sidebar;
