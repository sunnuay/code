import { Server, Settings } from "lucide-react";
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
	<aside className="w-64 bg-white border-r border-gray-200 flex flex-col shadow-sm z-10">
		<div className="h-16 flex items-center px-6 border-b border-gray-100">
			<Server className="text-blue-600 mr-3" size={24} />
			<h1 className="text-xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-blue-600 to-indigo-600">
				web
			</h1>
		</div>

		<nav className="flex-1 py-6 px-4 space-y-1">
			{menuItems.map((item) => {
				const Icon = item.icon;
				const isActive = activeTab === item.id;
				return (
					<button
						key={item.id}
						onClick={() => onTabChange(item.id)}
						className={`w-full flex items-center px-4 py-3 rounded-xl transition-all duration-200 ${
							isActive
								? "bg-blue-50 text-blue-700 shadow-sm"
								: "text-gray-600 hover:bg-gray-50 hover:text-gray-900"
						}`}
					>
						<Icon
							size={20}
							className={isActive ? "text-blue-600" : "text-gray-400"}
						/>
						<span className="ml-3 font-medium">{item.name}</span>
					</button>
				);
			})}
		</nav>

		<div className="p-4 border-t border-gray-100">
			<button className="w-full flex items-center px-4 py-2 text-gray-500 hover:text-gray-800 transition-colors">
				<Settings size={20} className="mr-3" />
				<span className="font-medium">系统设置</span>
			</button>
		</div>
	</aside>
);

export default Sidebar;
